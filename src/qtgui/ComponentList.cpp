#include <core/component/ComponentFactory.hpp>

#include "ComponentList.hpp"

ComponentList::ComponentList(Library *aLibrary, QObject *parent) :
  QAbstractListModel(parent),
  library(aLibrary)
{
  library->registerObserver(this);
}

ComponentList::~ComponentList()
{
  library->unregisterObserver(this);
  delete library;
}

int ComponentList::rowCount(const QModelIndex &) const
{
  return library->getComponents().size();
}

int ComponentList::columnCount(const QModelIndex &) const
{
  return 1;
}

QVariant ComponentList::data(const QModelIndex &index, int role) const
{
  switch (role) {
    case Qt::DisplayRole:
      return QString::fromStdString(library->getComponents()[index.row()]->getName());
  }

  return QVariant();
}

void ComponentList::addComponent(const QString &name)
{
  library->add(ComponentFactory::produce(name.toStdString()));
}

Component *ComponentList::getComponent(const QModelIndex &index) const
{
  return library->getComponents()[index.row()];
}

void ComponentList::delComponent(const QModelIndex &index)
{
  if (!index.isValid()) {
    return;
  }
  Component *component = library->getComponents()[index.row()];
  library->del(component);
}

Library *ComponentList::getLibrary() const
{
  return library;
}

void ComponentList::addComponent(const Library *, Component *)
{
  layoutChanged();
}

void ComponentList::delComponent(const Library *, Component *)
{
  layoutChanged();
}
