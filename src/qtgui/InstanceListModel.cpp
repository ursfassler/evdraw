// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "InstanceListModel.hpp"

#include <core/util/list.hpp>

InstanceListModel::InstanceListModel(Composition &aComposition, QObject *parent) :
  NameTypeModel(parent),
  composition(aComposition)
{
  setNameEditable(true);
  composition.registerObserver(this);
  for (Instance *instance : composition.getInstances()) {
    instance->ObserverCollection<InstanceObserver>::registerObserver(this);
  }
}

InstanceListModel::~InstanceListModel()
{
  for (Instance *instance : composition.getInstances()) {
    instance->ObserverCollection<InstanceObserver>::unregisterObserver(this);
  }
  composition.unregisterObserver(this);
}

int InstanceListModel::rowCount(const QModelIndex &) const
{
  return composition.getInstances().size();
}

QString InstanceListModel::getName(uint row) const
{
  const Instance *inst = getInstance(row);
  return QString::fromStdString(inst->getName());
}

void InstanceListModel::setName(uint row, QString name)
{
  Instance *inst = getInstance(row);
  inst->setName(name.toStdString());
}

QString InstanceListModel::getType(uint row) const
{
  const Instance *inst = getInstance(row);
  return QString::fromStdString(inst->getComponent()->getName());
}

Instance *InstanceListModel::getInstance(uint row) const
{
  return *std::next(composition.getInstances().begin(), row);
}

void InstanceListModel::instanceAdded(Instance *instance)
{
  layoutChanged();
  instance->ObserverCollection<InstanceObserver>::registerObserver(this);
}

void InstanceListModel::instanceRemoved(Instance *instance)
{
  instance->ObserverCollection<InstanceObserver>::unregisterObserver(this);
  layoutChanged();
}

void InstanceListModel::nameChanged(const Instance *instance)
{
  const auto &list = composition.getInstances();
  size_t row = indexOf(list.begin(), list.end(), instance);

  const QModelIndex idx = index(row, NAME_INDEX);
  dataChanged(idx,idx);
}
