// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "CompositionEditor.hpp"

#include <QGridLayout>

CompositionEditor::CompositionEditor(Composition &composition, QWidget *parent) :
  QWidget(parent),
  draw(composition, this),
  instances(composition, this),
  connections(composition, this)
{
  QGridLayout *layout = new QGridLayout();

  layout->addWidget(&draw, 0, 0, 2, 1);
  layout->addWidget(&instanceView, 0, 1, 1, 1);
  layout->addWidget(&connectionView, 1, 1, 1, 1);

  this->setLayout(layout);

  instanceView.setModel(&instances);
  connectionView.setModel(&connections);

  connect(&draw, SIGNAL(addInstance(Point,Composition&)), this, SIGNAL(addInstance(Point,Composition&)));
}

