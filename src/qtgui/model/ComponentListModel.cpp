// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include <core/component/ComponentFactory.hpp>

#include "ComponentListModel.hpp"

ComponentListModel::ComponentListModel(Library *aLibrary, QObject *parent) :
  NameTypeModel(parent),
  library(aLibrary),
  typeModel(new ImplementationTypeModel())
{
  setNameEditable(true);
  library->registerObserver(this);
}

ComponentListModel::~ComponentListModel()
{
  library->unregisterObserver(this);
  delete typeModel;
  delete library;
}

int ComponentListModel::rowCount(const QModelIndex &) const
{
  return library->getComponents().size();
}

void ComponentListModel::addComponent(const QString &name)
{
  library->addComponent(ComponentFactory::produce(name.toStdString()));
}

Component *ComponentListModel::getComponent(const QModelIndex &index) const
{
  return library->getComponents()[index.row()];
}

void ComponentListModel::deleteComponent(const QModelIndex &index)
{
  if (!index.isValid()) {
    return;
  }
  Component *component = library->getComponents()[index.row()];
  library->deleteComponent(component);
}

QModelIndex ComponentListModel::getIndex(Component *component) const
{
  const auto components = library->getComponents();
  const uint row = indexOf(components.begin(), components.end(), component);
  return index(row);
}

Library *ComponentListModel::getLibrary() const
{
  return library;
}

void ComponentListModel::componentAdded(Component *)
{
  layoutChanged();
}

void ComponentListModel::componentDeleted(Component *)
{
  layoutChanged();
}

QString ComponentListModel::getName(uint row) const
{
  const Component *component = getComponent(row);
  return QString::fromStdString(component->getName());
}

bool ComponentListModel::setName(uint row, QString name)
{
  Component *component = getComponent(row);
  component->setName(name.toStdString());
  return true;
}

QAbstractListModel *ComponentListModel::getTypes() const
{
  return typeModel;
}

QModelIndex ComponentListModel::getType(uint row) const
{
  const Component *component = getComponent(row);
  return typeModel->typeIndex(getImplementationType(component));
}

Component *ComponentListModel::getComponent(uint row) const
{
  return library->getComponents()[row];
}

ImplementationType ComponentListModel::getImplementationType(const Component *component) const
{
  ImplementationNameVisitor visitor;
  component->getImplementation()->accept(visitor);
  return visitor.type;
}


void ImplementationNameVisitor::visit(const Composition &)
{
  type = ImplementationType::Composition;
}

void ImplementationNameVisitor::visit(const NullImplementation &)
{
  type = ImplementationType::Empty;
}

