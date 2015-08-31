// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef INSTANCELISTMODEL_HPP
#define INSTANCELISTMODEL_HPP

#include <core/implementation/Composition.hpp>
#include <core/instance/Instance.hpp>

#include <QObject>
#include "NameTypeModel.hpp"

class InstanceListModel :
    public NameTypeModel,
    private CompositionObserver,
    private InstanceObserver
{
    Q_OBJECT
  public:
    explicit InstanceListModel(Composition &composition, QObject *parent);
    ~InstanceListModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const;

  protected:
    QString getName(uint row) const;
    void setName(uint row, QString name);
    QString getType(uint row) const;

  private:
    Composition &composition;

    Instance *getInstance(uint row) const;

    void instanceAdded(Instance *instance);
    void instanceRemoved(Instance *instance);

    void nameChanged(const Instance *instance);

};

#endif
