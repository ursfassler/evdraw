// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef PORTLISTMODEL_HPP
#define PORTLISTMODEL_HPP

#include <core/component/Component.hpp>
#include <core/visitor/NullConstVisitor.hpp>

#include "NameTypeModel.hpp"
#include "PortTypeModel.h"

class PortListModel :
    public NameTypeModel,
    private ComponentObserver
{
    Q_OBJECT
  public:
    explicit PortListModel(Component &component, QObject *parent = 0);
    ~PortListModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const;

    void delPort(const QModelIndex &index);
    void addPort(const QString &name);

    const Component *getComponent() const;
    QAbstractListModel *getTypes() const;

  protected:
    QString getName(uint row) const;
    bool setName(uint row, QString name);
    QModelIndex getType(uint row) const;
    bool setType(uint row, const QVariant &value);

  private:
    Component &component;
    PortTypeModel * const typeModel;

    QString getPortTypeName(const ComponentPort *port) const;
    ComponentPort *getPort(uint row) const;

    void portAdded(ComponentPort *port);
    void portDeleted(ComponentPort *port);
};

#endif
