#include "Workspace.hpp"

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
#include <file/xmlwriter/XmlWriter.hpp>

#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QDebug>

Workspace::Workspace(QWidget *parent) :
  QWidget(parent),
  drawTabs(this)
{
  QWidget *leftBar = new QWidget(this);
  QVBoxLayout *leftLayout = new QVBoxLayout;
  leftLayout->addWidget(&compList);
  leftLayout->addWidget(&portView);
  leftBar->setLayout(leftLayout);


  QHBoxLayout *layout = new QHBoxLayout;
  layout->addWidget(leftBar);
  layout->addWidget(&drawTabs);
  this->setLayout(layout);

  connect(&compList, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(openImplementation(QModelIndex)));
  connect(&compList, SIGNAL(clicked(QModelIndex)), this, SLOT(openComponent(QModelIndex)));
}

void Workspace::addComponent()
{
  componentModel->addComponent("lulu");
}

void Workspace::delComponent()
{
  QModelIndex selected = compList.currentIndex();
  componentModel->delComponent(selected);
}

void Workspace::openFile(const QString &filename)
{
  Library *lib = XmlReader::loadFile(filename.toStdString());
  componentModel = new ComponentList(lib);
  compList.setModel(componentModel);
}

void Workspace::saveFile(const QString &filename)
{
  XmlWriter::saveFile(filename.toStdString(), *componentModel->getLibrary());
}

void Workspace::openComponent(const QModelIndex &index)
{
  Component *comp = componentModel->getComponent(index);
  showComponent(comp);
}

void Workspace::showComponent(const Component *component)
{
  if (portModel != nullptr) {
    portModel->deleteLater();
  }
  portModel = new CompifaceModel(*component);
  portView.setModel(portModel);
}

void Workspace::openImplementation(const QModelIndex &index)
{
  Component *comp = componentModel->getComponent(index);
  ImplementationOpener opener(drawTabs);
  comp->getImplementation()->accept(opener);
}

ImplementationOpener::ImplementationOpener(QTabWidget &aDrawTabs) :
  drawTabs(aDrawTabs)
{
}

void ImplementationOpener::visit(Composition &composition)
{
  CompositionEditor *editor = new CompositionEditor(composition);
  drawTabs.addTab(editor, "lala");
  //  editor->show();
}

