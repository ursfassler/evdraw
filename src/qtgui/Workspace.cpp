// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "Workspace.hpp"

#include "CompositionEditor.hpp"
#include "view/ComboboxItemDelegate.hpp"
#include "view/modelfromtype.hpp"

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

#include <QVBoxLayout>
#include <QLabel>

#include <QDebug>

Workspace::Workspace(QWidget *parent) :
  QSplitter(Qt::Horizontal, parent),
  drawTabs(this)
{
  QWidget *leftBar = new QWidget(this);
  QVBoxLayout *leftLayout = new QVBoxLayout;
  leftLayout->addWidget(new QLabel("Components"));
  leftLayout->addWidget(&compView);
  leftLayout->addWidget(&componentEditor);
  leftBar->setLayout(leftLayout);

  this->addWidget(leftBar);
  this->addWidget(&drawTabs);

  compView.setItemDelegateForColumn(QtNameTypeItem<IComponent>::TYPE_INDEX, new ComboboxItemDelegate(modelFromTypeIndex<IComponent>)); //FIXME memory leak

  connect(&compView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(openImplementation(QModelIndex)));
  connect(&compView, SIGNAL(clicked(QModelIndex)), this, SLOT(openComponent(QModelIndex)));

  newFile();

  postcondition(componentModel != nullptr);
}

Workspace::~Workspace()
{
  removeLibrary();

  postcondition(componentModel == nullptr);
}

Library *Workspace::getLibrary() const
{
  return library;
}

void Workspace::addComponent()
{
  library->getComponents().add(ComponentFactory::produce("lulu"));
}

void Workspace::addPort()
{
  componentEditor.addPort();
}

void Workspace::delPort()
{
  componentEditor.delPort();
}

void Workspace::delComponent()
{
  QModelIndex selected = compView.currentIndex();
  const auto component = library->getComponents()[selected.row()];
  library->getComponents().remove(component);
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

  XmlWriter::saveFile(filename.toStdString(), *library);
}

void Workspace::openComponent(const QModelIndex &index)
{
  auto comp = library->getComponents()[index.row()];
  showComponent(comp);
}

void Workspace::showComponent(IComponent *component)
{
  componentEditor.setModel(component);
}

void Workspace::removed(IComponent *component)
{
  if (componentEditor.getModel() == component) {
    componentEditor.setModel(nullptr);
  }
}

void Workspace::openImplementation(const QModelIndex &index)
{
  auto comp = library->getComponents()[index.row()];
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
  auto component = library->getComponents()[idx.row()];
  Instance *inst = InstanceFactory::produce(component, "?", position);
  composition.getInstances().add(inst);
}

void Workspace::removeLibrary()
{
  while (drawTabs.count() > 0) {
    drawTabs.setCurrentIndex(0);
    drawTabs.currentWidget()->deleteLater();
    drawTabs.removeTab(0);
  }

  componentEditor.setModel(nullptr);

  if (componentModel != nullptr) {
    compView.setModel(nullptr);
    library->getComponents().unregisterObserver(this);
    delete componentModel;
    componentModel = nullptr;
  }

  delete library;
  library = nullptr;
}

void Workspace::newLibrary(Library *library)
{
  removeLibrary();

  precondition(componentModel == nullptr);

  componentModel = new ComponentListModel(library->getComponents());
  compView.setModel(componentModel);
  library->getComponents().registerObserver(this);

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

