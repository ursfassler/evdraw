#include "MainWindow.hpp"

#include <QMenuBar>
#include <QApplication>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  workspace(this)
{
  setCentralWidget(&workspace);

  QMenu *file = menuBar()->addMenu("File");
  file->addAction("Open", this, SLOT(openFile()));
  file->addAction("Save", this, SLOT(saveFile()));
  file->addAction("Exit", QApplication::instance(), SLOT(quit()));
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
