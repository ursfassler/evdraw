#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "Workspace.hpp"

#include <QMainWindow>


class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

  private slots:
    void openFile();
    void saveFile();

  private:
    Workspace workspace;

};

#endif // MAINWINDOW_HPP
