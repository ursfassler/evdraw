// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "ComponentEditor.hpp"

#include "ComboboxItemDelegate.hpp"

#include <QVBoxLayout>
#include <QLabel>

ComponentEditor::ComponentEditor(QWidget *parent) :
  QWidget(parent)
{
  QVBoxLayout *layout = new QVBoxLayout;
  layout->addWidget(new QLabel("Ports"));
  layout->addWidget(&portView);
  this->setLayout(layout);

  portView.setItemDelegateForColumn(PortListModel::TYPE_INDEX, new ComboboxItemDelegate(modelFromTypeIndex)); //FIXME memory leak
}

ComponentEditor::~ComponentEditor()
{
  if (portModel != nullptr) {
    delete portModel;
    portModel = nullptr;
  }
}

void ComponentEditor::setModel(Component *component)
{
  if (component == nullptr) {
    if (portModel != nullptr) {
      portView.setModel(nullptr);
      delete portModel;
      portModel = nullptr;
    }
  } else {
    if (portModel != nullptr) {
      portModel->deleteLater();
    }
    portModel = new PortListModel(component->getPorts());
    portView.setModel(portModel);
  }

  model = component;
}

Component *ComponentEditor::getModel() const
{
  return model;
}

void ComponentEditor::addPort()
{
  portModel->addPort("lolo");
}

void ComponentEditor::delPort()
{
  QModelIndex selected = portView.currentIndex();
  portModel->delPort(selected);
}
