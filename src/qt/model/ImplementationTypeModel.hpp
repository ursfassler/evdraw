// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef IMPLEMENTATIONTYPEMODEL_HPP
#define IMPLEMENTATIONTYPEMODEL_HPP

#include <core/implementation/ImplementationType.hpp>

#include <QAbstractListModel>

class ImplementationTypeModel :
    public QAbstractListModel
{
  public:
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QModelIndex typeIndex(ImplementationType type) const;
};

#endif // IMPLEMENTATIONTYPEMODEL_HPP
