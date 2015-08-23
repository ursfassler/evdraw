// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef WORKSPACE_HPP
#define WORKSPACE_HPP

#include "ComponentModel.hpp"
#include "CompositionEditor.hpp"
#include "CompifaceModel.hpp"

#include <core/visitor/NullVisitor.hpp>

#include <QWidget>
#include <QListView>
#include <QTabWidget>
#include <QListView>
#include <QTreeView>

class Workspace : public QWidget, private LibraryObserver
{
    Q_OBJECT
  public:
    explicit Workspace(QWidget *parent = 0);
    ~Workspace();

  signals:

  public slots:
    void addComponent();
    void addPort();
    void delComponent();
    void delPort();

  public slots:
    void newFile();
    void openFile(const QString &filename);
    void saveFile(const QString &filename);
    void openComponent(const QModelIndex &index);
    void openImplementation(const QModelIndex &index);

  private slots:
    void addInstance(Point position, Composition &composition);

  private:
    ComponentModel *componentModel = nullptr;
    QTreeView compView;
    CompifaceModel *portModel = nullptr;
    QTreeView portView;
    QTabWidget drawTabs;

    void removeLibrary();
    void newLibrary(Library *library);
    void showComponent(Component *component);
    void componentDeleted(Component *component);
};

class ImplementationOpener : public NullVisitor
{
  public:
    ImplementationOpener(QTabWidget &drawTabs, Workspace *workspace);

    void visit(Composition &composition);

  private:
    QTabWidget &drawTabs;
    Workspace * const workspace;
};


#endif // WORKSPACE_HPP
