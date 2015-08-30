// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include <core/component/ComponentFactory.hpp>

#include "ComponentModel.hpp"

ComponentModel::ComponentModel(Library *aLibrary, QObject *parent) :
  NameTypeModel(parent),
  library(aLibrary)
{
  library->registerObserver(this);
}

ComponentModel::~ComponentModel()
{
  library->unregisterObserver(this);
  delete library;
}

int ComponentModel::rowCount(const QModelIndex &) const
{
  return library->getComponents().size();
}

void ComponentModel::addComponent(const QString &name)
{
  library->addComponent(ComponentFactory::produce(name.toStdString()));
}

Component *ComponentModel::getComponent(const QModelIndex &index) const
{
  return library->getComponents()[index.row()];
}

void ComponentModel::deleteComponent(const QModelIndex &index)
{
  if (!index.isValid()) {
    return;
  }
  Component *component = library->getComponents()[index.row()];
  library->deleteComponent(component);
}

Library *ComponentModel::getLibrary() const
{
  return library;
}

void ComponentModel::componentAdded(Component *)
{
  layoutChanged();
}

void ComponentModel::componentDeleted(Component *)
{
  layoutChanged();
}

QString ComponentModel::getName(uint row) const
{
  const Component *component = library->getComponents()[row];
  return QString::fromStdString(component->getName());
}

QString ComponentModel::getType(uint row) const
{
  const Component *component = library->getComponents()[row];
  return getImplementationName(component);
}

QString ComponentModel::getImplementationName(const Component *component) const
{
  ImplementationNameVisitor visitor;
  component->getImplementation()->accept(visitor);
  return visitor.name;
}


void ImplementationNameVisitor::visit(const Composition &)
{
  name = "Composition";
}

void ImplementationNameVisitor::visit(const NullImplementation &)
{
  name = "empty";
}
