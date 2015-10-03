// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef INSTANCELISTMODEL_HPP
#define INSTANCELISTMODEL_HPP

#include <core/implementation/Composition.hpp>
#include <core/instance/Instance.hpp>
#include <core/component/Library.hpp>

#include <QObject>
#include "NameTypeModel.hpp"
#include "ComponentListModel.hpp"


class InstanceListModel :
    public NameTypeModel,
    private CompositionObserver,
    private InstanceObserver
{
    Q_OBJECT
  public:
    explicit InstanceListModel(Composition &composition, Library &library, QObject *parent);
    ~InstanceListModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const;

    QAbstractListModel *getTypes() const;

  protected:
    QString getName(uint row) const;
    bool setName(uint row, QString name);
    QModelIndex getType(uint row) const;

  private:
    Composition &composition;
    ComponentListModel * const typeModel;

    Instance *getInstance(uint row) const;
    uint getRow(const IInstance *instance) const;

    void instanceAdded(Instance *instance) override;
    void instanceRemoved(Instance *instance) override;

    void nameChanged(const IInstance *instance) override;
    void componentNameChanged(const IInstance *instance) override;
};

#endif
