// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "QtListFactory.hpp"

#include "QtNameTypeItem.hpp"
#include "ComponentItem.hpp"
#include "InstanceItem.hpp"
#include "PortItem.hpp"
#include "QtConnectionItem.hpp"

namespace QtListFactory
{

QtList<IComponent> *createComponentList(List<IComponent> &model, QObject *parent)
{
  const auto item = new QtNameTypeItem<IComponent>(new ComponentItem());
  return new QtList<IComponent>{model, item, parent};
}

QtList<ComponentPort> *createPortList(List<ComponentPort> &model, QObject *parent)
{
  const auto item = new QtNameTypeItem<ComponentPort>(new PortItem());
  return new QtList<ComponentPort>(model, item, parent);
}

QtList<IComponentInstance> *createInstanceList(List<IComponentInstance> &model, QtList<IComponent> *types, QObject *parent)
{
  auto instItem = new InstanceItem(types);
  const auto item = new QtNameTypeItem<IComponentInstance>(instItem);
  return new QtList<IComponentInstance>(model, item, parent);
}

QtList<Connection> *createConnectionList(List<Connection> &model, QObject *parent)
{
  auto const item = new QtConnectionItem();
  return new  QtList<Connection>(model, item, parent);
}

}
