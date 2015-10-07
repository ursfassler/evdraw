// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "ConnectionListModel.hpp"

#include <core/instance/InstancePort.hpp>


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





ConnectionListModel::ConnectionListModel(Composition &aComposition, QObject *parent) :
  QAbstractListModel(parent),
  composition(aComposition)
{
  composition.registerObserver(this);
}

ConnectionListModel::~ConnectionListModel()
{
  composition.unregisterObserver(this);
}

int ConnectionListModel::columnCount(const QModelIndex &) const
{
  return COLUMN_COUNT;
}

int ConnectionListModel::rowCount(const QModelIndex &) const
{
  return composition.getConnections().size();
}

QVariant ConnectionListModel::headerData(int section, Qt::Orientation, int role) const
{
  if (role != Qt::DisplayRole) {
    return QVariant();
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

  return QVariant();
}

QVariant ConnectionListModel::data(const QModelIndex &index, int role) const
{
  if (role != Qt::DisplayRole) {
    return QVariant();
  }

  const uint row = index.row();
  const uint column = index.column();
  const Connection *con = getConnection(row);

  IPort *port = nullptr;

  switch (column) {
    case SRC_INST_INDEX:
    case SRC_PORT_INDEX:
      port = con->getStartPort();
      break;
    case DST_INST_INDEX:
    case DST_PORT_INDEX:
      port = con->getEndPort();
      break;
  }

  if (port == nullptr) {
    return "<error>";
  }

  switch (column) {
    case SRC_INST_INDEX:
    case DST_INST_INDEX:
      return instanceName(*port);
    case SRC_PORT_INDEX:
    case DST_PORT_INDEX:
      return QString::fromStdString(port->getName());
  }

  return "<error>";
}

Connection *ConnectionListModel::getConnection(uint row) const
{
  return *std::next(composition.getConnections().begin(), row);
}

QString ConnectionListModel::instanceName(const IPort &port) const
{
  ConnectionEndpointNameVisitor visitor;
  port.accept(visitor);
  return visitor.instance;
}

void ConnectionListModel::connectionAdded(Connection *)
{
  layoutChanged();
}

void ConnectionListModel::connectionRemoved(Connection *)
{
  layoutChanged();
}









