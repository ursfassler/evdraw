// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "InstanceListModel.hpp"

#include <core/util/list.hpp>

InstanceListModel::InstanceListModel(Composition &aComposition, Library &aLibrary, QObject *parent) :
  NameTypeModel(parent),
  composition(aComposition),
  typeModel(new ComponentListModel(&aLibrary))
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

bool InstanceListModel::setName(uint row, QString name)
{
  Instance *inst = getInstance(row);
  inst->setName(name.toStdString());
  return true;
}

QAbstractListModel *InstanceListModel::getTypes() const
{
  return typeModel;
}

QModelIndex InstanceListModel::getType(uint row) const
{
  const Instance *inst = getInstance(row);
  return typeModel->getIndex(inst->getComponent());
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
  const size_t row = getRow(instance);
  const QModelIndex idx = index(row, NAME_INDEX);
  dataChanged(idx,idx);
}

void InstanceListModel::componentNameChanged(const Instance *instance)
{
  const size_t row = getRow(instance);
  const QModelIndex idx = index(row, TYPE_INDEX);
  dataChanged(idx,idx);
}

uint InstanceListModel::getRow(const Instance *instance) const
{
  const auto &list = composition.getInstances();
  return indexOf(list.begin(), list.end(), instance);
}
