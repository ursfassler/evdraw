#include "ComponentList.hpp"

ComponentList::ComponentList(Library *aLibrary, QObject *parent) :
  QAbstractListModel(parent),
  library(aLibrary)
{
}

ComponentList::~ComponentList()
{
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

Component *ComponentList::getComponent(const QModelIndex &index) const
{
  return library->getComponents()[index.row()];
}

Library *ComponentList::getLibrary() const
{
  return library;
}

