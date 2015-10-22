// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef QTNAMETYPEITEM_HPP
#define QTNAMETYPEITEM_HPP

#include "IQtItem.hpp"
#include "INameTypeItem.hpp"

template<class T>
class QtNameTypeItem :
    public IQtItem<T>
{
  public:
    QtNameTypeItem(INameTypeItem<T> &aModel) :
      model(aModel)
    {
    }

    int columnCount() const override final
    {
      return COLUMN_COUNT;
    }

    bool editable(int column) const override final
    {
      switch (column) {
        case NAME_INDEX:
          return model.isNameEditable();
        case TYPE_INDEX:
          return model.isTypeEditable();
      }

      return {};
    }

    QVariant headerData(int section, Qt::Orientation, int role) const override final
    {
      if (role != Qt::DisplayRole) {
        return {};
      }

      switch (section) {
        case NAME_INDEX:
          return "name";
        case TYPE_INDEX:
          return "type";
      }

      return {};
    }

    QVariant data(const T *item, int column, int role) const override final
    {
      switch (column) {
        case NAME_INDEX:
          switch (role) {
            case Qt::DisplayRole:
            case Qt::EditRole:
              return QString::fromStdString(model.getName(item));
            default:
              return {};
          }
        case TYPE_INDEX:
          const auto typeIndex = model.getType(item);
          const auto *typeModel = model.getTypeModel();
          const auto index = typeModel->index(typeIndex);
          return typeModel->data(index, role);
      }
      return {};
    }

    bool setData(T *item, int column, const QVariant &value) override final
    {
      switch (column) {
        case NAME_INDEX: {
            if (value.type() == QVariant::String) {
              model.setName(item, value.toString().toStdString());
              return true;
            }
            break;
          }
        case TYPE_INDEX: {
            if ((value.type() == QVariant::Int) || (value.type() == QVariant::UInt)) {
              bool ok = false;
              const auto uintValue = value.toInt(&ok);
              if (ok && (uintValue >= 0)) {
                model.setType(item, uintValue);
                return true;
              }
            }
            break;
          }
      }

      return false;
    }


  private:
    static const uint NAME_INDEX = 0;
    static const uint TYPE_INDEX = 1;
    static const uint COLUMN_COUNT = 2;

    INameTypeItem<T> &model;
};

#endif // QTNAMETYPEITEM_HPP
