#include "MainWindow.hpp"

#include "CompositionEditor.hpp"

#include <QMenuBar>
#include <QApplication>
#include <QFileDialog>

#include <core/connection/Connection.hpp>
#include <core/connection/ConnectionFactory.hpp>
#include <core/component/Component.hpp>
#include <core/component/InstanceAppearance.hpp>
#include <core/component/ComponentFactory.hpp>
#include <core/instance/InstancePort.hpp>
#include <core/instance/Instance.hpp>
#include <core/instance/InstanceFactory.hpp>
#include <core/implementation/Composition.hpp>
#include <file/xmlreader/XmlReader.hpp>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  componentView(this)
{
  setCentralWidget(&componentView);

  QMenu *file = menuBar()->addMenu("File");
  file->addAction("Open", this, SLOT(openFile()));
  file->addAction("Exit", QApplication::instance(), SLOT(quit()));

  connect(&componentView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(openComponent(QModelIndex)));
}

MainWindow::~MainWindow()
{
}

void MainWindow::openComponent(const QModelIndex &index)
{
  Component *comp = componentModel->getComponent(index);
  Composition *composition = dynamic_cast<Composition*>(comp->getImplementation());
  if (composition != nullptr) {
    CompositionEditor *editor = new CompositionEditor(*composition);
    editor->show();
  }
}

void MainWindow::openFile()
{
  const QString fileName = QFileDialog::getOpenFileName(this, "Open File");
  Library *lib = XmlReader::loadFile(fileName.toStdString());
  componentModel = new ComponentList(lib);
  componentView.setModel(componentModel);
}
