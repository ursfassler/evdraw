// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef COMPONENTLIST_HPP
#define COMPONENTLIST_HPP

#include <core/component/Library.hpp>
#include <core/component/Component.hpp>
#include <core/visitor/NullConstVisitor.hpp>

#include "NameTypeModel.hpp"

//TODO make names editable
class ComponentModel :
    public NameTypeModel,
    private LibraryObserver
{
    Q_OBJECT
  public:

    explicit ComponentModel(Library *library, QObject *parent = 0);
    ~ComponentModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const;

    void addComponent(const QString &name);
    Component *getComponent(const QModelIndex &index) const;
    void deleteComponent(const QModelIndex &index);

    Library *getLibrary() const;

  signals:

  public slots:

  protected:
    QString getName(uint row) const;
    QString getType(uint row) const;

  private:
    Library * const library;

    QString getImplementationName(const Component *component) const;

    void componentAdded(Component *component);
    void componentDeleted(Component *component);
};

class ImplementationNameVisitor : public NullConstVisitor
{
  public:
    void visit(const Composition &composition);
    void visit(const NullImplementation &nullImplementation) ;

    QString name;
};


#endif // COMPONENTLIST_HPP
