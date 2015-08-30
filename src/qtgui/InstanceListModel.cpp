// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "InstanceListModel.hpp"

InstanceListModel::InstanceListModel(Composition &aComposition, QObject *parent) :
  NameTypeModel(parent),
  composition(aComposition)
{
  composition.registerObserver(this);
}

InstanceListModel::~InstanceListModel()
{
  composition.unregisterObserver(this);
}

int InstanceListModel::rowCount(const QModelIndex &) const
{
  return composition.getInstances().size();
}

QString InstanceListModel::getName(uint row) const
{
  Instance *inst = getInstance(row);
  return QString::fromStdString(inst->getName());
}

QString InstanceListModel::getType(uint row) const
{
  Instance *inst = getInstance(row);
  return QString::fromStdString(inst->getComponent()->getName());
}

Instance *InstanceListModel::getInstance(uint row) const
{
  return *std::next(composition.getInstances().begin(), row);
}

void InstanceListModel::instanceAdded(Instance *)
{
  layoutChanged();
}

void InstanceListModel::instanceRemoved(Instance *)
{
  layoutChanged();
}
