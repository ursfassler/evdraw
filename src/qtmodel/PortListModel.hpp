// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef PORTLISTMODEL_HPP
#define PORTLISTMODEL_HPP

#include <core/component/ComponentPort.hpp>
#include <core/util/List.hpp>
#include <core/visitor/NullConstVisitor.hpp>

#include "NameTypeModel.hpp"
#include "PortTypeModel.hpp"

//TODO add tests

class PortListModel :
    public NameTypeModel,
    private ListObserver<ComponentPort>
{
    Q_OBJECT
  public:
    PortListModel(const PortListModel&) = delete;
    PortListModel &operator =(const PortListModel&) = delete;


    explicit PortListModel(List<ComponentPort> &ports, QObject *parent = 0);
    ~PortListModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    void delPort(const QModelIndex &index);
    void addPort(const QString &name);

    QAbstractListModel *getTypes() const override;

  protected:
    QString getName(uint row) const override;
    bool setName(uint row, QString name) override;
    QModelIndex getType(uint row) const override;
    bool setType(uint row, const QVariant &value) override;

  private:
    List<ComponentPort> &ports;
    PortTypeModel * const typeModel;

    QString getPortTypeName(const ComponentPort *port) const;
    ComponentPort *getPort(uint row) const;

    void added(ComponentPort *port) override;
    void removed(ComponentPort *port) override;
};

#endif
