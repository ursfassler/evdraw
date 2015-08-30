// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef COMPIFACEMODEL_HPP
#define COMPIFACEMODEL_HPP

#include <core/component/Component.hpp>
#include <core/visitor/NullConstVisitor.hpp>

#include "NameTypeModel.hpp"

class CompifaceModel :
    public NameTypeModel,
    private ComponentObserver
{
    Q_OBJECT
  public:
    explicit CompifaceModel(Component &component, QObject *parent = 0);
    ~CompifaceModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const;

    void delPort(const QModelIndex &index);
    void addPort(const QString &name);

    const Component *getComponent() const;

  protected:
    QString getName(uint row) const;
    void setName(uint row, QString name);
    QString getType(uint row) const;

  private:
    Component &component;

    QString getPortTypeName(const ComponentPort *port) const;
    ComponentPort *getPort(uint row) const;

    void portAdded(ComponentPort *port);
    void portDeleted(ComponentPort *port);
};

class PortTypeNameVisitor : public NullConstVisitor
{
  public:
    void visit(const Slot &port);
    void visit(const Signal &port);

    QString name;

};

#endif // COMPIFACEMODEL_HPP
