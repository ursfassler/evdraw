// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "CompositionEditor.hpp"
#include "view/ComboboxItemDelegate.hpp"
#include "view/modelfromtype.hpp"

#include <QVBoxLayout>
#include <QLabel>

CompositionEditor::CompositionEditor(Composition &composition, Library &library, QWidget *parent) :
  QSplitter(Qt::Horizontal, parent),
  draw(composition, this),
  componentModel{library.getComponents(), this},
  instances(composition.getInstances(), &componentModel, this),
  connections(composition.getConnections(), this)
{
  this->addWidget(&draw);

  QVBoxLayout *layout = new QVBoxLayout();
  layout->addWidget(new QLabel("Instances"));
  layout->addWidget(&instanceView);
  layout->addWidget(new QLabel("Connections"));
  layout->addWidget(&connectionView);

  QWidget *rightPanel = new QWidget();
  rightPanel->setLayout(layout);
  this->addWidget(rightPanel);

  instanceView.setItemDelegateForColumn(QtNameTypeItem<IComponentInstance>::TYPE_INDEX, new ComboboxItemDelegate(modelFromTypeIndex<IComponentInstance>)); //FIXME memory leak
  instanceView.setModel(&instances);
  connectionView.setModel(&connections);

  connect(&draw, SIGNAL(addInstance(Point,Composition&)), this, SIGNAL(addInstance(Point,Composition&)));
}

CompositionEditor::~CompositionEditor()
{
  connectionView.setModel(nullptr);
  instanceView.setModel(nullptr);
}

