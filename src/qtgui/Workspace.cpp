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
  leftLayout->addWidget(&compView);
  leftLayout->addWidget(&portView);
  leftBar->setLayout(leftLayout);


  QHBoxLayout *layout = new QHBoxLayout;
  layout->addWidget(leftBar);
  layout->addWidget(&drawTabs);
  this->setLayout(layout);

  connect(&compView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(openImplementation(QModelIndex)));
  connect(&compView, SIGNAL(clicked(QModelIndex)), this, SLOT(openComponent(QModelIndex)));
}

void Workspace::addComponent()
{
  componentModel->addComponent("lulu");
}

void Workspace::addPort()
{
  portModel->addPort("lolo");
}

void Workspace::delComponent()
{
  QModelIndex selected = compView.currentIndex();
  componentModel->deleteComponent(selected);
}

void Workspace::delPort()
{
  QModelIndex selected = portView.currentIndex();
  portModel->delPort(selected);
}

void Workspace::openFile(const QString &filename)
{
  Library *lib = XmlReader::loadFile(filename.toStdString());
  componentModel = new ComponentModel(lib);
  compView.setModel(componentModel);
  lib->registerObserver(this);
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

void Workspace::showComponent(Component *component)
{
  if (portModel != nullptr) {
    portModel->deleteLater();
  }
  portModel = new CompifaceModel(*component);
  portView.setModel(portModel);
}

void Workspace::componentDeleted(Component *component)
{
  if ((portModel != nullptr) && (portModel->getComponent() == component)) {
    portView.setModel(nullptr);
    delete portModel;
    portModel = nullptr;
  }
}

void Workspace::openImplementation(const QModelIndex &index)
{
  Component *comp = componentModel->getComponent(index);
  ImplementationOpener opener(drawTabs, this);
  comp->getImplementation()->accept(opener);
}

void Workspace::addInstance(Point position, Composition &composition)
{
  Component *component = componentModel->getLibrary()->getComponents()[0];
  Instance *inst = InstanceFactory::produce(component, "?", position);
  composition.addInstance(inst);
}

ImplementationOpener::ImplementationOpener(QTabWidget &aDrawTabs, Workspace *aWorkspace) :
  drawTabs(aDrawTabs),
  workspace(aWorkspace)
{
}

void ImplementationOpener::visit(Composition &composition)
{
  CompositionEditor *editor = new CompositionEditor(composition);
  drawTabs.addTab(editor, "lala");
  QObject::connect(editor, SIGNAL(addInstance(Point,Composition&)), workspace, SLOT(addInstance(Point,Composition&)));
}

