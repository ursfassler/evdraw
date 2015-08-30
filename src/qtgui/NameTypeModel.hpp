// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef NAMETYPEMODEL_HPP
#define NAMETYPEMODEL_HPP

#include <QObject>
#include <QAbstractListModel>

class NameTypeModel : public QAbstractListModel
{
  public:
    explicit NameTypeModel(QObject *parent);

    int columnCount(const QModelIndex &parent) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

  protected:
    static const uint NAME_INDEX = 0;
    static const uint TYPE_INDEX = 1;
    static const uint COLUMN_COUNT = 2;

    bool nameEditable = false;
    void setNameEditable(bool editable);

    virtual QString getName(uint row) const = 0;
    virtual void setName(uint row, QString name);
    virtual QString getType(uint row) const = 0;
};

#endif // NAMETYPEMODEL_HPP
