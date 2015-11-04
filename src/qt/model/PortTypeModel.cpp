// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "PortTypeModel.hpp"

int PortTypeModel::rowCount(const QModelIndex &) const
{
  return portTypeList().size();
}

QVariant PortTypeModel::data(const QModelIndex &index, int role) const
{
  switch (role) {
    case Qt::DisplayRole: {
      const PortType type = portTypeList()[index.row()];
      const QString typeName = QString::fromStdString(toString(type));
      return typeName;
    }
    case Qt::EditRole: {
      return index.row();
    }
  }
  return QVariant();
}

