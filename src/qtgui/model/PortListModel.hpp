// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef PORTLISTMODEL_HPP
#define PORTLISTMODEL_HPP

#include <core/component/Component.hpp>
#include <core/visitor/NullConstVisitor.hpp>

#include "NameTypeModel.hpp"
#include "PortTypeModel.hpp"

class PortListModel :
    public NameTypeModel,
    private ComponentObserver
{
    Q_OBJECT
  public:
    explicit PortListModel(Component &component, QObject *parent = 0);
    ~PortListModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    void delPort(const QModelIndex &index);
    void addPort(const QString &name);

    const Component *getComponent() const;
    QAbstractListModel *getTypes() const override;

  protected:
    QString getName(uint row) const override;
    bool setName(uint row, QString name) override;
    QModelIndex getType(uint row) const override;
    bool setType(uint row, const QVariant &value) override;

  private:
    Component &component;
    PortTypeModel * const typeModel;

    QString getPortTypeName(const ComponentPort *port) const;
    ComponentPort *getPort(uint row) const;

    void portAdded(ComponentPort *port) override;
    void portDeleted(ComponentPort *port) override;
};

#endif
