#include "CompifaceModel.hpp"

CompifaceModel::CompifaceModel(const Component &aComponent, QObject *parent) :
  QAbstractListModel(parent),
  component(aComponent)
{
}

int CompifaceModel::rowCount(const QModelIndex &) const
{
  return component.getPortLeft().size() + component.getPortRight().size();
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
    ComponentPort *port;
    if (row < component.getPortLeft().size()) {
      port = component.getPortLeft()[row];
    } else {
      port = component.getPortRight()[row-component.getPortLeft().size()];
    }
    return QString::fromStdString(port->getName());
  } else {
    return "lolo";
  }
}
