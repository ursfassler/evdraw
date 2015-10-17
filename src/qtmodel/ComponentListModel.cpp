// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include <core/component/ComponentFactory.hpp>

#include "ComponentListModel.hpp"


class ImplementationNameVisitor : public NullConstVisitor
{
  public:
    void visit(const Composition &)
    {
      type = ImplementationType::Composition;
    }

    void visit(const NullImplementation &)
    {
      type = ImplementationType::Empty;
    }

    ImplementationType type{};
};



ComponentListModel::ComponentListModel(List<Component> &aComponents, QObject *parent) :
  NameTypeModel(parent),
  components(aComponents),
  typeModel(new ImplementationTypeModel())
{
  setNameEditable(true);
  components.registerObserver(this);
}

ComponentListModel::~ComponentListModel()
{
  components.unregisterObserver(this);
  delete typeModel;
}

int ComponentListModel::rowCount(const QModelIndex &) const
{
  return components.size();
}

void ComponentListModel::addComponent(const QString &name)
{
  components.add(ComponentFactory::produce(name.toStdString()));
}

Component *ComponentListModel::getComponent(const QModelIndex &index) const
{
  return components[index.row()];
}

void ComponentListModel::deleteComponent(const QModelIndex &index)
{
  if (!index.isValid()) {
    return;
  }
  Component *component = components[index.row()];
  components.remove(component);
}

QModelIndex ComponentListModel::getIndex(Component *component) const
{
  const uint row = components.indexOf(component);
  return index(row);
}

void ComponentListModel::added(Component *)
{
  layoutChanged();
}

void ComponentListModel::removed(Component *)
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
  return components[row];
}

ImplementationType ComponentListModel::getImplementationType(const Component *component) const
{
  ImplementationNameVisitor visitor;
  component->getImplementation()->accept(visitor);
  return visitor.type;
}
