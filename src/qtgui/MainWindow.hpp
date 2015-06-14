#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "ComponentList.hpp"

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

  private:
    QListView componentView;
    ComponentList *componentModel = nullptr;

};

#endif // MAINWINDOW_HPP
