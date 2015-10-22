// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef INSTANCELISTMODEL_HPP
#define INSTANCELISTMODEL_HPP

#include <core/implementation/Composition.hpp>
#include <core/instance/Instance.hpp>
#include <core/component/Component.hpp>

#include <QObject>
#include "NameTypeModel.hpp"
#include "ComponentItem.hpp"

//TODO use QtList instead from NameTypeModel

class InstanceListModel :
    public NameTypeModel,
    private ListObserver<Instance>,
    private InstanceObserver
{
    Q_OBJECT
  public:
    InstanceListModel(const InstanceListModel&) = delete;
    InstanceListModel &operator =(const InstanceListModel&) = delete;

    explicit InstanceListModel(List<Instance> &instances, List<IComponent> &components, QObject *parent);
    ~InstanceListModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const;

    QAbstractListModel *getTypes() const;

  protected:
    QString getName(uint row) const;
    bool setName(uint row, QString name);
    QModelIndex getType(uint row) const;

  private:
    List<Instance> &composition;
    ComponentListModel * const typeModel;

    Instance *getInstance(uint row) const;
    uint getRow(const IInstance *instance) const;

    void added(Instance *instance) override;
    void removed(Instance *instance) override;

    void nameChanged(const IInstance *instance) override;
    void componentNameChanged(const IInstance *instance) override;
};

#endif
