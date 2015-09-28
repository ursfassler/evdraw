// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "ConnectionListModel.hpp"

#include <core/instance/InstancePort.hpp>

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

  const QPair<QString,QString> epname = endpointName(*port);

  switch (column) {
    case SRC_INST_INDEX:
    case DST_INST_INDEX:
      return epname.first;
    case SRC_PORT_INDEX:
    case DST_PORT_INDEX:
      return epname.second;
  }

  return "<error>";
}

Connection *ConnectionListModel::getConnection(uint row) const
{
  return *std::next(composition.getConnections().begin(), row);
}

QPair<QString,QString> ConnectionListModel::endpointName(const IPort &port) const
{
  ConnectionEndpointNameVisitor visitor;
  port.accept(visitor);
  return QPair<QString,QString>(visitor.instance, visitor.port);
}

void ConnectionListModel::connectionAdded(Connection *)
{
  layoutChanged();
}

void ConnectionListModel::connectionRemoved(Connection *)
{
  layoutChanged();
}



void ConnectionEndpointNameVisitor::visit(const Instance &instance)
{
  this->instance = QString::fromStdString(instance.getName());
}

void ConnectionEndpointNameVisitor::visit(const CompositionInstance &instance)
{
  this->instance = "self";
}

void ConnectionEndpointNameVisitor::visit(const InstancePort &port)
{
  port.getInstance()->accept(*this);
  this->port = QString::fromStdString(port.getName());
}

