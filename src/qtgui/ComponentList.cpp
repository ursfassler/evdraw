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

Library *ComponentList::getLibrary() const
{
  return library;
}

void ComponentList::addComponent(const Library *, Component *)
{
  const int row = rowCount();
  beginInsertRows(QModelIndex(), row, row);
  endInsertRows();
}
