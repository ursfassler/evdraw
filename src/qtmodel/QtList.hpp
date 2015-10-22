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

    Qt::ItemFlags flags(const QModelIndex &index) const override
    {
      Qt::ItemFlags flags = QAbstractListModel::flags(index);

      if (item.editable(index.column())) {
        flags |= Qt::ItemIsEditable;
      }

      return flags;
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

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole)
    {
      if (role != Qt::EditRole) {
        return false;
      }

      const auto row = index.row();
      const auto con = list[row];
      const auto column = index.column();

      return item.setData(con, column, value);
    }

    QModelIndex getIndex(const T* item) const
    {
      const auto idx = list.indexOf(item);
      return index(idx);
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
