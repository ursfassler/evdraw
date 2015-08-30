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

  switch (index.column()) {
    case NAME_INDEX:
      if (nameEditable) {
        flags |= Qt::ItemIsEditable;
      }
      break;
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
  if (role != Qt::DisplayRole) {
    return QVariant();
  }

  const uint row = index.row();
  const uint column = index.column();
  switch (column) {
    case NAME_INDEX:
      return getName(row);
    case TYPE_INDEX:
      return getType(row);
  }

  return "<error>";
}

bool NameTypeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
  if (role != Qt::EditRole) {
    return false;
  }

  if (index.column() != NAME_INDEX) {
    return false;
  }

  const unsigned row = index.row();

  const QString newName = value.toString();
  const QString oldName = getName(row);
  if (newName == oldName) {
    return false;
  }

  setName(row, newName);

  return true;
}

void NameTypeModel::setNameEditable(bool editable)
{
  nameEditable = editable;
}

void NameTypeModel::setName(uint, QString)
{
}

