// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "QtItemIntMock.hpp"


int QtItemIntMock::columnCount() const
{
  columnCount_called++;
  return columnCount_return;
}

bool QtItemIntMock::editable(int column) const
{
  editable_column = column;
  return editable_return;
}

QVariant QtItemIntMock::headerData(int section, Qt::Orientation orientation, int role) const
{
  (void)section;
  (void)orientation;
  (void)role;

  headerData_called++;
  return headerData_return;
}

QVariant QtItemIntMock::data(const int *item, int column, int role) const
{
  (void)item;
  (void)column;
  (void)role;

  data_called++;
  return data_return;
}

bool QtItemIntMock::setData(int *item, int column, const QVariant &value)
{
  (void)item;
  (void)column;
  (void)value;

  setData_called++;
  return setData_return;
}
