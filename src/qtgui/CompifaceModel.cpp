// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "CompifaceModel.hpp"

CompifaceModel::CompifaceModel(Component &aComponent, QObject *parent) :
  NameTypeModel(parent),
  component(aComponent)
{
  setNameEditable(true);
  component.registerObserver(this);
}

CompifaceModel::~CompifaceModel()
{
  component.unregisterObserver(this);
}

int CompifaceModel::rowCount(const QModelIndex &) const
{
  return component.getPorts().size();
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

QString CompifaceModel::getName(uint row) const
{
  const ComponentPort *port = getPort(row);
  return QString::fromStdString(port->getName());
}

void CompifaceModel::setName(uint row, QString name)
{
  ComponentPort *port = getPort(row);
  port->setName(name.toStdString());
}

QString CompifaceModel::getType(uint row) const
{
  const ComponentPort *port = getPort(row);
  return getPortTypeName(port);
}

ComponentPort *CompifaceModel::getPort(uint row) const
{
  return component.getPorts()[row];
}

QString CompifaceModel::getPortTypeName(const ComponentPort *port) const
{
  PortTypeNameVisitor visitor;
  port->accept(visitor);
  return visitor.name;
}


void PortTypeNameVisitor::visit(const Slot &)
{
  name = "Slot";
}

void PortTypeNameVisitor::visit(const Signal &)
{
  name = "Signal";
}
