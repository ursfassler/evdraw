#ifndef WORKSPACE_HPP
#define WORKSPACE_HPP

#include "ComponentList.hpp"
#include "CompositionEditor.hpp"
#include "CompifaceModel.hpp"

#include <core/visitor/NullVisitor.hpp>

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
    void addPort();
    void delComponent();
    void delPort();

  public slots:
    void openFile(const QString &filename);
    void saveFile(const QString &filename);
    void openComponent(const QModelIndex &index);
    void openImplementation(const QModelIndex &index);

  private slots:
    void addInstance(Point position, Composition &composition);

  private:
    ComponentList *componentModel = nullptr;
    QListView compList;
    CompifaceModel *portModel = nullptr;
    QTreeView portView;
    QTabWidget drawTabs;

    void showComponent(Component *component);
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
