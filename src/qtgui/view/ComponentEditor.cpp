// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "ComponentEditor.hpp"

#include "ComboboxItemDelegate.hpp"
#include "modelfromtype.hpp"

#include <qt/model/QtListFactory.hpp>

#include <QVBoxLayout>
#include <QLabel>

ComponentEditor::ComponentEditor(QWidget *parent) :
  QWidget(parent)
{
  QVBoxLayout *layout = new QVBoxLayout;
  layout->addWidget(new QLabel("Ports"));
  layout->addWidget(&portView);
  this->setLayout(layout);

  portView.setItemDelegateForColumn(QtNameTypeItem<ComponentPort>::TYPE_INDEX, new ComboboxItemDelegate(modelFromTypeIndex<ComponentPort>)); //FIXME memory leak
}

ComponentEditor::~ComponentEditor()
{
  if (portModel != nullptr) {
    delete portModel;
    portModel = nullptr;
  }
}

void ComponentEditor::setModel(IComponent *component)
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
    portModel = QtListFactory::createPortList(component->getPorts(), this);
    portView.setModel(portModel);
  }

  model = component;
}

IComponent *ComponentEditor::getModel() const
{
  return model;
}

void ComponentEditor::addPort()
{
  model->getPorts().add(new ComponentPort("lolo", PortType::Slot));
}

void ComponentEditor::delPort()
{
  QModelIndex selected = portView.currentIndex();
  const auto port = model->getPorts()[selected.row()];
  model->getPorts().remove(port);
}
