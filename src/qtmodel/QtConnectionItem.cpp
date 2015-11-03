// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "QtConnectionItem.hpp"

#include <core/visitor/NullConstVisitor.hpp>
#include <core/instance/InstancePort.hpp>
#include <core/instance/Instance.hpp>
#include "../core/util/error.hpp"


class ConnectionEndpointNameVisitor :
    public NullConstVisitor
{
  public:
    void visit(const Instance &instance) override
    {
      this->instance = QString::fromStdString(instance.getName());
    }

    void visit(const CompositionInstance &) override
    {
      this->instance = "self";
    }

    void visit(const InstancePort &port) override
    {
      port.getInstance()->accept(*this);
    }

    QString instance{"<error>"};
};






int QtConnectionItem::columnCount() const
{
  return COLUMN_COUNT;
}

bool QtConnectionItem::editable(int) const
{
  return false;
}

QVariant QtConnectionItem::headerData(int section, Qt::Orientation, int role) const
{
  if (role != Qt::DisplayRole) {
    return {};
  }

  switch (section) {
    case SRC_INST_INDEX:
      return "src inst";
    case SRC_PORT_INDEX:
      return "src port";
    case DST_INST_INDEX:
      return "dst inst";
    case DST_PORT_INDEX:
      return "dst port";
  }

  return {};
}

QVariant QtConnectionItem::data(const Connection *connection, int column, int role) const
{
  if (role != Qt::DisplayRole) {
    return {};
  }

  const IPort *port = portOfColumn(connection, column);
  if (port == nullptr) {
    return {};
  }

  return portName(port, column);
}

IPort *QtConnectionItem::portOfColumn(const Connection *connection, int column) const
{
  switch (column) {
    case SRC_INST_INDEX:
    case SRC_PORT_INDEX:
      return connection->getStartPort();
    case DST_INST_INDEX:
    case DST_PORT_INDEX:
      return connection->getEndPort();
  }

  return nullptr;
}

QVariant QtConnectionItem::portName(const IPort *port, int column) const
{
  switch (column) {
    case SRC_INST_INDEX:
    case DST_INST_INDEX:
      return instanceName(*port);
    case SRC_PORT_INDEX:
    case DST_PORT_INDEX:
      return QString::fromStdString(port->getName());
  }

  return {};
}

QString QtConnectionItem::instanceName(const IPort &port) const
{
  ConnectionEndpointNameVisitor visitor;
  port.accept(visitor);
  return visitor.instance;
}


bool QtConnectionItem::setData(Connection *, int, const QVariant &)
{
  return false;
}

void QtConnectionItem::added(Connection *)
{
}

void QtConnectionItem::removed(Connection *)
{
}
