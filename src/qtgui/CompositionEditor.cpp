// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "CompositionEditor.hpp"
#include "view/ComboboxItemDelegate.hpp"

#include <QGridLayout>
#include <QLabel>

CompositionEditor::CompositionEditor(Composition &composition, Library &library, QWidget *parent) :
  QWidget(parent),
  draw(composition, this),
  instances(composition, library, this),
  connections(composition, this)
{
  QGridLayout *layout = new QGridLayout();

  layout->addWidget(&draw, 0, 0, 4, 1);
  layout->addWidget(new QLabel("Instances"), 0, 1, 1, 1);
  layout->addWidget(&instanceView, 1, 1, 1, 1);
  layout->addWidget(new QLabel("Connections"), 2, 1, 1, 1);
  layout->addWidget(&connectionView, 3, 1, 1, 1);

  this->setLayout(layout);

  instanceView.setItemDelegateForColumn(InstanceListModel::TYPE_INDEX, new ComboboxItemDelegate(modelFromTypeIndex)); //FIXME memory leak
  instanceView.setModel(&instances);
  connectionView.setModel(&connections);

  connect(&draw, SIGNAL(addInstance(Point,Composition&)), this, SIGNAL(addInstance(Point,Composition&)));
}

