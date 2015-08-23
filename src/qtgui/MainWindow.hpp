// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

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
    void createFileMenu();
    void createEditMenu();

};

#endif // MAINWINDOW_HPP
