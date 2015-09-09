// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "NameTypeModel.hpp"


NameTypeModel::NameTypeModel(QObject *parent) :
  QAbstractListModel(parent)
{
}

int NameTypeModel::columnCount(const QModelIndex &) const
{
  return COLUMN_COUNT;
}

Qt::ItemFlags NameTypeModel::flags(const QModelIndex &index) const
{
  Qt::ItemFlags flags = QAbstractListModel::flags(index);

  if ((index.column() >= 0) && (uint(index.column()) < COLUMN_COUNT)) {
    if (editable[index.column()]) {
      flags |= Qt::ItemIsEditable;
    }
  }

  return flags;
}

QVariant NameTypeModel::headerData(int section, Qt::Orientation, int role) const
{
  if (role != Qt::DisplayRole) {
    return QVariant();
  }

  switch (section) {
    case NAME_INDEX:
      return "name";
    case TYPE_INDEX:
      return "type";
  }

  return QVariant();
}

QVariant NameTypeModel::data(const QModelIndex &index, int role) const
{
  const uint row = index.row();
  const uint column = index.column();

  switch (column) {
    case NAME_INDEX:
      switch (role) {
        case Qt::DisplayRole:
        case Qt::EditRole:
          return getName(row);
        default:
          return QVariant();
      }
    case TYPE_INDEX:
      return getType(row).data(role);
  }
  return QVariant();
}

bool NameTypeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
  if (role != Qt::EditRole) {
    return false;
  }

  const unsigned row = index.row();

  switch (index.column()) {
    case NAME_INDEX: {
      const QString newName = value.toString();
      const QString oldName = getName(row);
      if (newName == oldName) {
        return false;
      }
      return setName(row, newName);
    }
    case TYPE_INDEX: {
      return setType(row, value);
    }
  }

  return false;
}

void NameTypeModel::setNameEditable(bool editable)
{
  this->editable[NAME_INDEX] = editable;
}

void NameTypeModel::setTypeEditable(bool editable)
{
  this->editable[TYPE_INDEX] = editable;
}

bool NameTypeModel::setName(uint, QString)
{
  return false;
}

bool NameTypeModel::setType(uint, const QVariant &)
{
  return false;
}
