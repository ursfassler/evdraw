// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "PortListModel.hpp"

#include "PortTypeModel.h"

#include <string>

PortListModel::PortListModel(Component &aComponent, QObject *parent) :
  NameTypeModel(parent),
  component(aComponent),
  typeModel(new PortTypeModel())
{
  setNameEditable(true);
  setTypeEditable(true);
  component.registerObserver(this);
}

PortListModel::~PortListModel()
{
  component.unregisterObserver(this);
  delete typeModel;
}

int PortListModel::rowCount(const QModelIndex &) const
{
  return component.getPorts().size();
}

void PortListModel::delPort(const QModelIndex &index)
{
  if (!index.isValid()) {
    return;
  }
  ComponentPort *port = component.getPorts()[index.row()];
  component.deletePort(port);
}

void PortListModel::addPort(const QString &name)
{
  component.addPort(new ComponentPort(name.toStdString(), PortType::Slot));
}

const Component *PortListModel::getComponent() const
{
  return &component;
}

void PortListModel::portAdded(ComponentPort *)
{
  layoutChanged();
}

void PortListModel::portDeleted(ComponentPort *)
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
  return getTypes()->index(uint(port->getType()), 0);  //FIXME memory leak?
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

  ComponentPort *port = component.getPorts()[row];
  const PortType portType = portTypeFromUint(type);
  port->setType(portType);
  return true;
}

ComponentPort *PortListModel::getPort(uint row) const
{
  return component.getPorts()[row];
}

QString PortListModel::getPortTypeName(const ComponentPort *port) const
{
  const std::string name = toString(port->getType());
  return QString::fromStdString(name);
}
