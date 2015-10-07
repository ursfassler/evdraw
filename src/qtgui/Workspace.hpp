// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef WORKSPACE_HPP
#define WORKSPACE_HPP

#include <qtmodel/ComponentListModel.hpp>
#include <qtmodel/PortListModel.hpp>

#include <core/visitor/NullVisitor.hpp>
#include <core/Point.hpp>

#include <QWidget>
#include <QListView>
#include <QTabWidget>
#include <QTreeView>
#include <QSplitter>

class Workspace :
    public QSplitter,
    private LibraryObserver
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
    PortListModel *portModel = nullptr;
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
    ImplementationOpener(QTabWidget &drawTabs, Workspace *workspace, QString name);

    void visit(Composition &composition);

  private:
    QTabWidget &drawTabs;
    Workspace * const workspace;
    QString name;
};


#endif // WORKSPACE_HPP
