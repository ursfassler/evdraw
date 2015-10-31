// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "ComponentItem.hpp"

#include "../core/implementation/ImplementationType.hpp"

ComponentItem::ComponentItem()
{
}

bool ComponentItem::isNameEditable() const
{
  return true;
}

bool ComponentItem::isTypeEditable() const
{
  return false;
}

QAbstractListModel *ComponentItem::getTypeModel()
{
  return &typeModel;
}

std::string ComponentItem::getName(const IComponent *item) const
{
  return item->getName();
}

void ComponentItem::setName(IComponent *item, const std::string &value)
{
  item->setName(value);
}

unsigned ComponentItem::getType(const IComponent *item) const
{
  const auto type = item->getImplementation()->getType();
  return uintFromImplementationType(type);
}

void ComponentItem::setType(IComponent *, unsigned)
{
}





ComponentListModel::ComponentListModel(List<IComponent> &aModel, QObject *parent) :
  QtList<IComponent>{aModel, ComponentListModel::item(), parent}
{
}

QtNameTypeItem<IComponent> &ComponentListModel::item()
{
  static ComponentItem comp;
  static QtNameTypeItem<IComponent> item{comp};
  return item;
}
