// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef NAMETYPEITEMMOCK_HPP
#define NAMETYPEITEMMOCK_HPP

#include <qtmodel/INameTypeItem.hpp>

#include <QVariant>

template<class T>
class NameTypeItemMock :
    public INameTypeItem<T>
{
  public:
    QAbstractListModel *typeModel{nullptr};
    QAbstractListModel *getTypeModel() override
    {
      return typeModel;
    }

    std::string name{};
    std::string getName(const T*) const override
    {
      return name;
    }

    void setName(T*, const std::string &value) override
    {
      name = value;
    }

    unsigned type{};
    unsigned getType(const T*) const override
    {
      return type;
    }

    void setType(T*, unsigned value) override
    {
      type = value;
    }

    bool nameEditable{};
    bool isNameEditable() const override
    {
      return nameEditable;
    }

    bool typeEditable{};
    bool isTypeEditable() const override
    {
      return typeEditable;
    }
};

#endif // NAMETYPEITEMMOCK_HPP
