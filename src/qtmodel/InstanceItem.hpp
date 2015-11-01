// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef INSTANCEITEM_HPP
#define INSTANCEITEM_HPP

#include "INameTypeItem.hpp"
#include "QtList.hpp"
#include "../core/instance/IComponentInstance.hpp"
#include "../core/component/IComponent.hpp"

class InstanceItem final :
    public ANameTypeItem<IComponentInstance>,
    private InstanceObserver
{
  public:
    InstanceItem(const InstanceItem &) = delete;
    InstanceItem &operator =(const InstanceItem &) =delete;


    InstanceItem(QtList<IComponent> *typeModel);

    bool isNameEditable() const override final;
    bool isTypeEditable() const override final;

    QAbstractListModel *getTypeModel() const override final;

    std::string getName(const IComponentInstance* item) const override final;
    void setName(IComponentInstance* item, const std::string &value) override final;
    unsigned getType(const IComponentInstance* item) const override final;
    void setType(IComponentInstance* item, unsigned value) override final;

    void added(IComponentInstance* item) override final;
    void removed(IComponentInstance* item) override final;

  private:
    QtList<IComponent> * const typeModel;

    void nameChanged(IInstance *instance) override final;
    void componentNameChanged(IInstance *instance) override final;
};


#include "QtList.hpp"
#include "QtNameTypeItem.hpp"

//TODO remove
class InstanceListModel :
    public QtList<IComponentInstance>
{
  public:
    InstanceListModel(List<IComponentInstance> &aModel, QtList<IComponent> *typeModel, QObject *parent = 0);

    static QtNameTypeItem<IComponentInstance> *item(QtList<IComponent> *typeModel);

};
#endif // INSTANCEITEM_HPP
