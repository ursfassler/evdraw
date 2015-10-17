// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "PortListModel.hpp"

#include "PortTypeModel.hpp"

#include <string>

PortListModel::PortListModel(List<ComponentPort> &aPorts, QObject *parent) :
  NameTypeModel(parent),
  ports(aPorts),
  typeModel(new PortTypeModel())
{
  setNameEditable(true);
  setTypeEditable(true);
  ports.registerObserver(this);
}

PortListModel::~PortListModel()
{
  ports.unregisterObserver(this);
  delete typeModel;
}

int PortListModel::rowCount(const QModelIndex &) const
{
  return ports.size();
}

void PortListModel::delPort(const QModelIndex &index)
{
  if (!index.isValid()) {
    return;
  }
  ComponentPort *port = ports[index.row()];
  ports.remove(port);
}

void PortListModel::addPort(const QString &name)
{
  ports.add(new ComponentPort(name.toStdString(), PortType::Slot));
}

void PortListModel::added(ComponentPort *)
{
  layoutChanged();
}

void PortListModel::removed(ComponentPort *)
{
  layoutChanged();
}

QString PortListModel::getName(uint row) const
{
  const ComponentPort *port = getPort(row);
  return QString::fromStdString(port->getName());
}

bool PortListModel::setName(uint row, QString name)
{
  ComponentPort *port = getPort(row);
  port->setName(name.toStdString());
  return true;
}

QAbstractListModel *PortListModel::getTypes() const
{
  return typeModel;
}

QModelIndex PortListModel::getType(uint row) const
{
  const ComponentPort *port = getPort(row);
  return typeModel->index(uint(port->getType()), 0);
}

bool PortListModel::setType(uint row, const QVariant &value)
{
  bool ok = false;
  const uint type = value.toUInt(&ok);
  if (!ok) {
    throw std::invalid_argument("expected uint");
  }
  if (type >= uint(typeModel->rowCount())) {
    throw std::invalid_argument("type out of range");
  }

  ComponentPort *port = ports[row];
  const PortType portType = portTypeFromUint(type);
  port->setType(portType);
  return true;
}

ComponentPort *PortListModel::getPort(uint row) const
{
  return ports[row];
}

QString PortListModel::getPortTypeName(const ComponentPort *port) const
{
  const std::string name = toString(port->getType());
  return QString::fromStdString(name);
}
