// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef COMPONENTITEM_HPP
#define COMPONENTITEM_HPP

#include "INameTypeItem.hpp"

#include "ImplementationTypeModel.hpp"

#include <core/component/Component.hpp>

class ComponentItem final :
    public ANameTypeItem<IComponent>,
    private ComponentObserver
{
  public:
    ComponentItem(const ComponentItem &) = delete;
    ComponentItem &operator =(const ComponentItem &) =delete;


    ComponentItem();
    ~ComponentItem();

    bool isNameEditable() const override final;
    bool isTypeEditable() const override final;

    QAbstractListModel *getTypeModel() const override final;

    std::string getName(const IComponent* item) const override final;
    void setName(IComponent* item, const std::string &value) override final;
    unsigned getType(const IComponent* item) const override final;
    void setType(IComponent* item, unsigned value) override final;

    void added(IComponent* item) override final;
    void removed(IComponent* item) override final;

  private:
    ImplementationTypeModel * const typeModel;

    void nameChanged(IComponent *) override final;

};

#endif // COMPONENTITEM_HPP
