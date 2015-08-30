// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef INSTANCELISTMODEL_HPP
#define INSTANCELISTMODEL_HPP

#include <core/implementation/Composition.hpp>

#include <QObject>
#include "NameTypeModel.hpp"

//TODO make names editable
class InstanceListModel :
    public NameTypeModel,
    private CompositionObserver
{
    Q_OBJECT
  public:
    explicit InstanceListModel(Composition &composition, QObject *parent);
    ~InstanceListModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const;

  protected:
    QString getName(uint row) const;
    QString getType(uint row) const;

  private:
    Composition &composition;

    Instance *getInstance(uint row) const;

    void instanceAdded(Instance *instance);
    void instanceRemoved(Instance *instance);

};

#endif
