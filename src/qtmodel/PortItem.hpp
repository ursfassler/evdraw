// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef PORTITEM_HPP
#define PORTITEM_HPP

#include "INameTypeItem.hpp"
#include "PortTypeModel.hpp"

#include <core/component/ComponentPort.hpp>

class PortItem final :
    public ANameTypeItem<ComponentPort>,
    private ComponentPortObserver
{
  public:
    PortItem(const PortItem &) = delete;
    PortItem &operator =(const PortItem &) =delete;

    PortItem();
    ~PortItem();


    bool isNameEditable() const override final;
    bool isTypeEditable() const override final;

    QAbstractListModel *getTypeModel() const override final;

    std::string getName(const ComponentPort* item) const override final;
    void setName(ComponentPort* item, const std::string &value) override final;
    unsigned getType(const ComponentPort* item) const override final;
    void setType(ComponentPort* item, unsigned value) override final;

    void added(ComponentPort *item) override final;
    void removed(ComponentPort *item) override final;

  private:
    void nameChanged(ComponentPort *port) override final;
    void typeChanged(ComponentPort *port) override final;

    PortTypeModel * const typeModel;
};



#include "QtList.hpp"
#include "QtNameTypeItem.hpp"

//TODO remove
class PortListModel :
    public QtList<ComponentPort>
{
  public:
    PortListModel(List<ComponentPort> &aModel, QObject *parent = 0);

    static QtNameTypeItem<ComponentPort> *item();

};


#endif // PORTITEM_HPP
