// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef QTLIST_HPP
#define QTLIST_HPP

#include "IQtItem.hpp"

#include <core/util/List.hpp>

#include <QObject>
#include <QAbstractListModel>

//TODO merge with NameTypeModel and InstanceListModel
//TODO send signal with pointer to item and column that changed

template<class T>
class QtList :
    public QAbstractListModel,
    private ListObserver<T>
{
  public:
    QtList(const QtList&) = delete;
    QtList &operator =(const QtList&) = delete;


    explicit QtList(List<T> &aModel, IQtItem<T> &aItem, QObject *parent = 0) :
      QAbstractListModel{parent},
      item{aItem},
      list{aModel}
    {
      list.registerObserver(this);
    }

    ~QtList() override
    {
      list.unregisterObserver(this);
    }


    int columnCount(const QModelIndex & = QModelIndex()) const override
    {
      return item.columnCount();
    }

    int rowCount(const QModelIndex & = QModelIndex()) const override
    {
      return list.size();
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override
    {
      return item.headerData(section, orientation, role);
    }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override
    {
      const auto row = index.row();
      const auto con = list[row];
      const auto column = index.column();

      return item.data(con, column, role);
    }

  private:
    IQtItem<T> &item;
    List<T> &list;

    void added(T*) override
    {
      layoutChanged();
    }

    void removed(T*) override
    {
      layoutChanged();
    }

};

#endif // QTLIST_HPP
