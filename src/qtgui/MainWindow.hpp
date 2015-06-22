#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "ComponentList.hpp"

#include <core/visitor/DefaultVisitor.hpp>

#include <QMainWindow>
#include <QListView>

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

  private slots:
    void openComponent(const QModelIndex &index);
    void openFile();
    void saveFile();

  private:
    QListView componentView;
    ComponentList *componentModel = nullptr;

};

class ImplementationOpener : public DefaultVisitor
{
  public:
    void visit(Composition &composition);
};


#endif // MAINWINDOW_HPP
