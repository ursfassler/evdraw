#include "MainWindow.hpp"

#include <QMenuBar>
#include <QApplication>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  workspace(this)
{
  setCentralWidget(&workspace);

  createFileMenu();
  createEditMenu();
}

void MainWindow::createFileMenu()
{
  QMenu *menu = menuBar()->addMenu("File");
  menu->addAction("Open", this, SLOT(openFile()));
  menu->addAction("Save", this, SLOT(saveFile()));
  menu->addAction("Exit", QApplication::instance(), SLOT(quit()));
}

void MainWindow::createEditMenu()
{
  QMenu *menu = menuBar()->addMenu("Edit");
  menu->addAction("Add Component", &workspace, SLOT(addComponent()));
  menu->addAction("Add Port", &workspace, SLOT(addPort()));
  menu->addAction("Delete Component", &workspace, SLOT(delComponent()));
  menu->addAction("Delete Port", &workspace, SLOT(delPort()));
}


MainWindow::~MainWindow()
{
}


void MainWindow::openFile()
{
  const QString fileName = QFileDialog::getOpenFileName(this, "Open File");
  if (!fileName.isNull()) {
    workspace.openFile(fileName);
  }
}

void MainWindow::saveFile()
{
  const QString fileName = QFileDialog::getSaveFileName(this, "Save File");
  if (!fileName.isNull()) {
    workspace.saveFile(fileName);
  }
}
