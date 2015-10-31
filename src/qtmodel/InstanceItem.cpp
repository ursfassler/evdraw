// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "InstanceItem.hpp"
#include "../core/util/contract.hpp"

InstanceItem::InstanceItem(QtList<IComponent> *aTypeModel) :
  typeModel{aTypeModel}
{
}

bool InstanceItem::isTypeEditable() const
{
  return false;
}

void InstanceItem::setType(IComponentInstance*, unsigned)
{
}

void InstanceItem::added(IComponentInstance *item)
{
  item->registerObserver(this);
}

void InstanceItem::removed(IComponentInstance *item)
{
  item->unregisterObserver(this);
}

void InstanceItem::nameChanged(IInstance *instance)
{
  //TODO remove cast
  auto inst = dynamic_cast<IComponentInstance*>(instance);
  precondition(inst != nullptr);

  notifyNameChange(inst);
}

void InstanceItem::componentNameChanged(IInstance *instance)
{
  //TODO remove cast
  auto inst = dynamic_cast<IComponentInstance*>(instance);
  precondition(inst != nullptr);

  notifyTypeChange(inst);
}

QAbstractListModel *InstanceItem::getTypeModel()
{
  return typeModel;
}

unsigned InstanceItem::getType(const IComponentInstance *item) const
{
  const auto component = item->getComponent();
  return typeModel->getIndex(component).row();  //TODO add indexOf to QtList or return QModelIndex?
}

bool InstanceItem::isNameEditable() const
{
  return true;
}

std::string InstanceItem::getName(const IComponentInstance *item) const
{
  return item->getName();
}

void InstanceItem::setName(IComponentInstance *item, const std::string &value)
{
  item->setName(value);
}



InstanceListModel::InstanceListModel(List<IComponentInstance> &aModel, QtList<IComponent> *typeModel, QObject *parent) :
  QtList<IComponentInstance>{aModel, InstanceListModel::item(typeModel), parent}
{
}

QtNameTypeItem<IComponentInstance> *InstanceListModel::item(QtList<IComponent> *typeModel)
{
  return new QtNameTypeItem<IComponentInstance>(new InstanceItem(typeModel));
}
