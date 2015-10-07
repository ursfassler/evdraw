// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef COMPONENTLISTMODEL_HPP
#define COMPONENTLISTMODEL_HPP

#include <core/component/Library.hpp>
#include <core/component/Component.hpp>
#include <core/visitor/NullConstVisitor.hpp>

#include "NameTypeModel.hpp"
#include "ImplementationTypeModel.hpp"

//TODO add tests

class ComponentListModel :
    public NameTypeModel,
    private LibraryObserver
{
    Q_OBJECT
  public:
    ComponentListModel(const ComponentListModel &) = delete;
    ComponentListModel &operator =(const ComponentListModel&) = delete;


    explicit ComponentListModel(Library *library, QObject *parent = 0);
    ~ComponentListModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const;

    void addComponent(const QString &name);
    Component *getComponent(const QModelIndex &index) const;
    void deleteComponent(const QModelIndex &index);
    QModelIndex getIndex(Component *component) const;

    Library *getLibrary() const;

    QAbstractListModel *getTypes() const;

  signals:

  public slots:

  protected:
    QString getName(uint row) const;
    bool setName(uint row, QString name);
    QModelIndex getType(uint row) const;

  private:
    Library * const library;
    ImplementationTypeModel * const typeModel;

    Component *getComponent(uint row) const;
    ImplementationType getImplementationType(const Component *component) const;

    void componentAdded(Component *component);
    void componentDeleted(Component *component);
};

#endif
