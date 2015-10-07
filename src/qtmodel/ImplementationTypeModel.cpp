// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "ImplementationTypeModel.hpp"

int ImplementationTypeModel::rowCount(const QModelIndex &) const
{
  return implementationTypeList().size();
}

QVariant ImplementationTypeModel::data(const QModelIndex &index, int role) const
{
  const ImplementationType type = implementationTypeList()[index.row()];
  switch (role) {
    case Qt::DisplayRole:
      return QString::fromStdString(toString(type));
    case Qt::EditRole:
      return uintFromImplementationType(type);
  }
  return QVariant();
}

QModelIndex ImplementationTypeModel::typeIndex(ImplementationType type) const
{
  const uint idx = uintFromImplementationType(type);
  return index(idx);
}
