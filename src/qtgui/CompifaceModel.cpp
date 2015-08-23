#include "CompifaceModel.hpp"

CompifaceModel::CompifaceModel(Component &aComponent, QObject *parent) :
  QAbstractListModel(parent),
  component(aComponent)
{
  component.registerObserver(this);
}

CompifaceModel::~CompifaceModel()
{
  component.unregisterObserver(this);
}

QVariant CompifaceModel::headerData(int section, Qt::Orientation, int role) const
{
  if (role != Qt::DisplayRole) {
    return QVariant();
  }

  switch(ColumnType(section)) {
    case ColumnType::Name: return "name";
    case ColumnType::Type: return "type";
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

  const unsigned row = index.row();
  const ComponentPort *port = component.getPorts()[row];
  return getColumnString(port, ColumnType(index.column()));
}

QString CompifaceModel::getColumnString(const ComponentPort *port, ColumnType type) const
{
  switch(type) {
    case ColumnType::Name:
        return QString::fromStdString(port->getName());
    case ColumnType::Type:
        return getPortTypeName(port);
    default:
      return "<error>";
  }
}

QString CompifaceModel::getPortTypeName(const ComponentPort *port) const
{
  PortTypeNameVisitor visitor;
  port->accept(visitor);
  return visitor.name;
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


void PortTypeNameVisitor::visit(const Slot &)
{
  name = "Slot";
}

void PortTypeNameVisitor::visit(const Signal &)
{
  name = "Signal";
}
