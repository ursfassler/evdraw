// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef COMPONENTITEM_HPP
#define COMPONENTITEM_HPP

#include "INameTypeItem.hpp"

#include "../core/component/Component.hpp"
#include "ImplementationTypeModel.hpp"

class ComponentItem final :
    public ANameTypeItem<IComponent>,
    private ComponentObserver
{
  public:
    ComponentItem();

    bool isNameEditable() const override final;
    bool isTypeEditable() const override final;

    QAbstractListModel *getTypeModel() override final;

    std::string getName(const IComponent* item) const override final;
    void setName(IComponent* item, const std::string &value) override final;
    unsigned getType(const IComponent* item) const override final;
    void setType(IComponent* item, unsigned value) override final;

    void added(IComponent* item) override final;
    void removed(IComponent* item) override final;

  private:
    ImplementationTypeModel typeModel{};

    void nameChanged(IComponent *) override final;

};


#include "QtList.hpp"
#include "QtNameTypeItem.hpp"

//TODO remove
class ComponentListModel :
    public QtList<IComponent>
{
  public:
    ComponentListModel(List<IComponent> &aModel, QObject *parent = 0);

    static QtNameTypeItem<IComponent> *item();

};



#endif // COMPONENTITEM_HPP
