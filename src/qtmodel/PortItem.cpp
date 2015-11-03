// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "PortItem.hpp"

PortItem::PortItem() :
  typeModel{new PortTypeModel()}
{
}

PortItem::~PortItem()
{
  delete typeModel;
}

bool PortItem::isNameEditable() const
{
  return true;
}

bool PortItem::isTypeEditable() const
{
  return true;
}

QAbstractListModel *PortItem::getTypeModel() const
{
  return typeModel;
}

std::string PortItem::getName(const ComponentPort *item) const
{
  return item->getName();
}

void PortItem::setName(ComponentPort *item, const std::string &value)
{
  item->setName(value);
}

unsigned PortItem::getType(const ComponentPort *item) const
{
  return uintFromPortType(item->getType());
}

void PortItem::setType(ComponentPort *item, unsigned value)
{
  item->setType(portTypeFromUint(value));
}

void PortItem::added(ComponentPort *item)
{
  item->registerObserver(this);
}

void PortItem::removed(ComponentPort *item)
{
  item->unregisterObserver(this);
}

void PortItem::nameChanged(ComponentPort *port)
{
  notifyNameChange(port);
}

void PortItem::typeChanged(ComponentPort *port)
{
  notifyTypeChange(port);
}
