// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef PORTTYPEMODEL_H
#define PORTTYPEMODEL_H

#include <core/component/PortType.hpp>

#include <QAbstractListModel>

class PortTypeModel :
    public QAbstractListModel
{
  public:
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

};

#endif // PORTTYPEMODEL_H
