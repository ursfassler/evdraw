// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "Workspace.hpp"

#include "CompositionEditor.hpp"
#include "view/ComboboxItemDelegate.hpp"

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
#include <QLabel>

#include <QDebug>

Workspace::Workspace(QWidget *parent) :
  QWidget(parent),
  drawTabs(this)
{
  QWidget *leftBar = new QWidget(this);
  QVBoxLayout *leftLayout = new QVBoxLayout;
  leftLayout->addWidget(new QLabel("Components"));
  leftLayout->addWidget(&compView);
  leftLayout->addWidget(new QLabel("Ports"));
  leftLayout->addWidget(&portView);
  leftBar->setLayout(leftLayout);


  QHBoxLayout *layout = new QHBoxLayout;
  layout->addWidget(leftBar);
  layout->addWidget(&drawTabs);
  this->setLayout(layout);

  compView.setItemDelegateForColumn(InstanceListModel::TYPE_INDEX, new ComboboxItemDelegate(modelFromTypeIndex)); //FIXME memory leak
  portView.setItemDelegateForColumn(InstanceListModel::TYPE_INDEX, new ComboboxItemDelegate(modelFromTypeIndex)); //FIXME memory leak

  connect(&compView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(openImplementation(QModelIndex)));
  connect(&compView, SIGNAL(clicked(QModelIndex)), this, SLOT(openComponent(QModelIndex)));

  newFile();
}

Workspace::~Workspace()
{
  removeLibrary();
}

Library *Workspace::getLibrary() const
{
  return library;
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

void Workspace::newFile()
{
  Library *lib = new Library();
  newLibrary(lib);
}

void Workspace::openFile(const QString &filename)
{
  Library *lib = XmlReader::loadFile(filename.toStdString());
  newLibrary(lib);
}

void Workspace::saveFile(const QString &filename)
{
  Q_ASSERT(componentModel != nullptr);

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
  portModel = new PortListModel(*component);
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
  ImplementationOpener opener(drawTabs, this, QString::fromStdString(comp->getName()));
  comp->getImplementation()->accept(opener);
}

void Workspace::addInstance(Point position, Composition &composition)
{
  QModelIndexList selected = compView.selectionModel()->selectedIndexes();
  if (selected.empty()) {
    return;
  }

  QModelIndex idx = selected.first();
  Component *component = componentModel->getComponent(idx);
  Instance *inst = InstanceFactory::produce(component, "?", position);
  composition.addInstance(inst);
}

void Workspace::removeLibrary()
{
  while (drawTabs.count() > 0) {
    drawTabs.setCurrentIndex(0);
    drawTabs.currentWidget()->deleteLater();
    drawTabs.removeTab(0);
  }

  if (portModel != nullptr) {
    portModel->deleteLater();
    portModel = nullptr;
  }

  if (componentModel != nullptr) {
    componentModel->getLibrary()->unregisterObserver(this);
    componentModel->deleteLater();
    componentModel = nullptr;
  }
  library = nullptr;
}

void Workspace::newLibrary(Library *library)
{
  removeLibrary();

  componentModel = new ComponentListModel(library);
  compView.setModel(componentModel); //FIXME memory leak
  library->registerObserver(this);

  this->library = library;
}

ImplementationOpener::ImplementationOpener(QTabWidget &aDrawTabs, Workspace *aWorkspace, QString aName) :
  drawTabs(aDrawTabs),
  workspace(aWorkspace),
  name(aName)
{
}

void ImplementationOpener::visit(Composition &composition)
{
  CompositionEditor *editor = new CompositionEditor(composition, *workspace->getLibrary());
  drawTabs.addTab(editor, name);
  QObject::connect(editor, SIGNAL(addInstance(Point,Composition&)), workspace, SLOT(addInstance(Point,Composition&)));
}

