#include "MainWindow.hpp"

#include <QGraphicsScene>
#include <QGraphicsView>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  scene(this),
  view(&scene)
{
  setCentralWidget(&view);
}

MainWindow::~MainWindow()
{
}

QGraphicsScene &MainWindow::getScene()
{
  return scene;
}
