// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef QTNAMETYPEITEM_HPP
#define QTNAMETYPEITEM_HPP

#include "IQtItem.hpp"
#include "INameTypeItem.hpp"

template<class T>
class QtNameTypeItem :
    public AQtItem<T>
{
  public:
    QtNameTypeItem(const QtNameTypeItem&) = delete;
    QtNameTypeItem &operator =(const QtNameTypeItem&) = delete;


    QtNameTypeItem(INameTypeItem<T> *aModel) :
      model(aModel)
    {
      aModel->addNameListener([this](T* item){this->notify(item, NAME_INDEX);});
      aModel->addTypeListener([this](T* item){this->notify(item, TYPE_INDEX);});
    }

    virtual ~QtNameTypeItem()
    {
      delete model;
    }

    void added(T *item) override final
    {
      model->added(item);
    }

    void removed(T *item) override final
    {
      model->removed(item);
    }

    int columnCount() const override final
    {
      return COLUMN_COUNT;
    }

    bool editable(int column) const override final
    {
      switch (column) {
        case NAME_INDEX:
          return model->isNameEditable();
        case TYPE_INDEX:
          return model->isTypeEditable();
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
              return QString::fromStdString(model->getName(item));
            default:
              return {};
          }
        case TYPE_INDEX:
          const auto typeIndex = model->getType(item);
          const auto *typeModel = model->getTypeModel();
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
              model->setName(item, value.toString().toStdString());
              return true;
            }
            break;
          }
        case TYPE_INDEX: {
            if ((value.type() == QVariant::Int) || (value.type() == QVariant::UInt)) {
              bool ok = false;
              const auto uintValue = value.toInt(&ok);
              if (ok && (uintValue >= 0)) {
                model->setType(item, uintValue);
                return true;
              }
            }
            break;
          }
      }

      return false;
    }

    static const uint NAME_INDEX = 0;
    static const uint TYPE_INDEX = 1;

  private:
    static const uint COLUMN_COUNT = 2;

    INameTypeItem<T> * const model;
};

#endif // QTNAMETYPEITEM_HPP
