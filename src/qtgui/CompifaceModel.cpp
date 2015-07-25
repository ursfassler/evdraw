#include "CompifaceModel.hpp"

CompifaceModel::CompifaceModel(Component &aComponent, QObject *parent) :
  QAbstractListModel(parent),
  component(aComponent)
{
}

QVariant CompifaceModel::headerData(int section, Qt::Orientation orientation, int role) const
{
  if (role != Qt::DisplayRole) {
    return QVariant();
  }

  switch(section) {
    case 0: return "name";
    case 1: return "type";
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

  if (index.column() == 0) {
    const unsigned row = index.row();
    const ComponentPort *port = component.getPorts()[row];
    return QString::fromStdString(port->getName());
  } else {
    return "lolo";
  }
}

void CompifaceModel::delPort(const QModelIndex &index)
{
  if (!index.isValid()) {
    return;
  }
  ComponentPort *port = component.getPorts()[index.row()];
  component.delPort(port);
}
