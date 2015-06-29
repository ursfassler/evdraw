#ifndef WORKSPACE_HPP
#define WORKSPACE_HPP

#include "ComponentList.hpp"
#include "CompositionEditor.hpp"
#include "CompifaceModel.hpp"

#include <core/visitor/DefaultVisitor.hpp>

#include <QWidget>
#include <QListView>
#include <QTabWidget>
#include <QListView>
#include <QTreeView>

class Workspace : public QWidget
{
    Q_OBJECT
  public:
    explicit Workspace(QWidget *parent = 0);

  signals:

  public slots:
    void addComponent();

  public slots:
    void openFile(const QString &filename);
    void saveFile(const QString &filename);
    void openComponent(const QModelIndex &index);
    void openImplementation(const QModelIndex &index);

  private:
    ComponentList *componentModel = nullptr;
    QListView compList;
    CompifaceModel *portModel = nullptr;
    QTreeView portView;
    QTabWidget drawTabs;

    void showComponent(const Component *component);
};

class ImplementationOpener : public DefaultVisitor
{
  public:
    ImplementationOpener(QTabWidget &drawTabs);

    void visit(Composition &composition);

  private:
    QTabWidget &drawTabs;
};


#endif // WORKSPACE_HPP
