// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "CompifaceModel.hpp"

CompifaceModel::CompifaceModel(Component &aComponent, QObject *parent) :
  QAbstractListModel(parent),
  component(aComponent)
{
  component.registerObserver(this);
}

CompifaceModel::~CompifaceModel()
{
  component.unregisterObserver(this);
}

Qt::ItemFlags CompifaceModel::flags(const QModelIndex &index) const
{
  const ColumnType type = ColumnType(index.column());
  Qt::ItemFlags flags = QAbstractListModel::flags(index);
  if (type == ColumnType::Name) {
    flags |= Qt::ItemIsEditable;
  }
  return flags;
}

bool CompifaceModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
  if (role != Qt::EditRole) {
    return false;
  }

  const ColumnType type = ColumnType(index.column());
  if (type != ColumnType::Name) {
    return false;
  }

  const unsigned row = index.row();
  ComponentPort *port = component.getPorts()[row];

  port->setName(value.toString().toStdString());

  dataChanged(index, index, {role});
  return true;
}

QVariant CompifaceModel::headerData(int section, Qt::Orientation, int role) const
{
  if (role != Qt::DisplayRole) {
    return QVariant();
  }

  switch(ColumnType(section)) {
    case ColumnType::Name: return "name";
    case ColumnType::Type: return "type";
  }

  return QVariant();
}

int CompifaceModel::rowCount(const QModelIndex &) const
{
  return component.getPorts().size();
}

int CompifaceModel::columnCount(const QModelIndex &) const
{
  return 2;
}

QVariant CompifaceModel::data(const QModelIndex &index, int role) const
{
  if (role != Qt::DisplayRole) {
    return QVariant();
  }

  const unsigned row = index.row();
  const ComponentPort *port = component.getPorts()[row];
  return getColumnString(port, ColumnType(index.column()));
}

QString CompifaceModel::getColumnString(const ComponentPort *port, ColumnType type) const
{
  switch(type) {
    case ColumnType::Name:
        return QString::fromStdString(port->getName());
    case ColumnType::Type:
        return getPortTypeName(port);
    default:
      return "<error>";
  }
}

QString CompifaceModel::getPortTypeName(const ComponentPort *port) const
{
  PortTypeNameVisitor visitor;
  port->accept(visitor);
  return visitor.name;
}

void CompifaceModel::delPort(const QModelIndex &index)
{
  if (!index.isValid()) {
    return;
  }
  ComponentPort *port = component.getPorts()[index.row()];
  component.deletePort(port);
}

void CompifaceModel::addPort(const QString &name)
{
  component.addPort(new Slot(name.toStdString()));
}

const Component *CompifaceModel::getComponent() const
{
  return &component;
}

void CompifaceModel::portAdded(ComponentPort *)
{
  layoutChanged();
}

void CompifaceModel::portDeleted(ComponentPort *)
{
  layoutChanged();
}


void PortTypeNameVisitor::visit(const Slot &)
{
  name = "Slot";
}

void PortTypeNameVisitor::visit(const Signal &)
{
  name = "Signal";
}
