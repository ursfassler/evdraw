// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef WORKSPACE_HPP
#define WORKSPACE_HPP

#include "view/ComponentEditor.hpp"

#include <qtmodel/ComponentItem.hpp>
#include <qtmodel/PortItem.hpp>

#include <core/visitor/NullVisitor.hpp>
#include <core/Point.hpp>

#include <QWidget>
#include <QListView>
#include <QTabWidget>
#include <QTreeView>
#include <QSplitter>

class Workspace :
    public QSplitter,
    private ListObserver<IComponent>
{
    Q_OBJECT
  public:
    explicit Workspace(QWidget *parent = 0);
    ~Workspace();

    Library *getLibrary() const;

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
    Library *library = nullptr;
    ComponentListModel *componentModel = nullptr;
    QTreeView compView;
    ComponentEditor componentEditor;
    QTabWidget drawTabs;

    void removeLibrary();
    void newLibrary(Library *library);
    void showComponent(IComponent *component);
    void removed(IComponent *component) override;
};

class ImplementationOpener : public NullVisitor
{
  public:
    ImplementationOpener(QTabWidget &drawTabs, Workspace *workspace, QString name);

    void visit(Composition &composition);

  private:
    QTabWidget &drawTabs;
    Workspace * const workspace;
    QString name;
};


#endif // WORKSPACE_HPP
