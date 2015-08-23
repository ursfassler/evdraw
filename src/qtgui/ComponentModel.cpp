#include <core/component/ComponentFactory.hpp>

#include "ComponentModel.hpp"

ComponentModel::ComponentModel(Library *aLibrary, QObject *parent) :
  QAbstractListModel(parent),
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

int ComponentModel::columnCount(const QModelIndex &) const
{
  return COLUMN_COUNT;
}

QVariant ComponentModel::headerData(int section, Qt::Orientation, int role) const
{
  if (role != Qt::DisplayRole) {
    return QVariant();
  }

  switch (section) {
    case NAME_INDEX:
      return "name";
    case TYPE_INDEX:
      return "type";
  }

  return QVariant();
}

QVariant ComponentModel::data(const QModelIndex &index, int role) const
{
  if (role != Qt::DisplayRole) {
    return QVariant();
  }

  const Component *component = library->getComponents()[index.row()];
  const uint column = index.column();
  switch (column) {
    case NAME_INDEX:
      return QString::fromStdString(component->getName());
    case TYPE_INDEX:
      return getImplementationName(component);
  }

  return "<error>";
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
