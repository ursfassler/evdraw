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


    explicit QtList(List<T> &aModel, IQtItem<T> *aItemModel, QObject *parent = 0) :
      QAbstractListModel{parent},
      itemModel{aItemModel},
      list{aModel}
    {
      aItemModel->addListener(changed);
      list.registerObserver(this);
      for (auto itr : aModel) {
        aItemModel->added(itr);
      }
    }

    ~QtList() override
    {
      list.unregisterObserver(this);
      delete itemModel;
    }


    int columnCount(const QModelIndex & = QModelIndex()) const override
    {
      return itemModel->columnCount();
    }

    int rowCount(const QModelIndex & = QModelIndex()) const override
    {
      return list.size();
    }

    Qt::ItemFlags flags(const QModelIndex &index) const override
    {
      Qt::ItemFlags flags = QAbstractListModel::flags(index);

      if (itemModel->editable(index.column())) {
        flags |= Qt::ItemIsEditable;
      }

      return flags;
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override
    {
      return itemModel->headerData(section, orientation, role);
    }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override
    {
      const auto row = index.row();
      const auto con = list[row];
      const auto column = index.column();

      return itemModel->data(con, column, role);
    }

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole)
    {
      if (role != Qt::EditRole) {
        return false;
      }

      const auto row = index.row();
      const auto con = list[row];
      const auto column = index.column();

      return itemModel->setData(con, column, value);
    }

    QModelIndex getIndex(const T* item) const
    {
      const auto idx = list.indexOf(item);
      return index(idx);
    }

  private:
    IQtItem<T> *itemModel;
    List<T> &list;

    void added(T *item) override
    {
      itemModel->added(item);
      layoutChanged();
    }

    void removed(T *item) override
    {
      itemModel->removed(item);
      layoutChanged();
    }

    const ChangeListener<T> changed =
        [this](T *item, int column)
    {
      const auto row = list.indexOf(item);
      const auto idx = index(row, column);
      dataChanged(idx, idx);
    };

};

#endif // QTLIST_HPP
