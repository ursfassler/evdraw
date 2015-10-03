// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "CompositionDraw.hpp"

#include "graphicItems/convert.hpp"

#include <core/component/InstanceAppearance.hpp>
#include <core/instance/InstanceFactory.hpp>

#include <QDebug>

CompositionDraw::CompositionDraw(Composition &aComposition, QWidget *parent) :
  QGraphicsView(parent),
  scene(this),
  selfInst{*aComposition.getSelfInstance(), aComposition},
  updater(scene, aComposition),
  composition(aComposition)
{
  setScene(&scene);

  QFont font("Sans", 0.6 * puToScene(InstanceAppearance::textHeight()));
  scene.setFont(font);

  updateSceneRect();

  scene.addItem(&selfInst);
  composition.getSelfInstance()->registerObserver(this);

  connect(&scene, SIGNAL(removeFromModel(QGraphicsItem*)), this, SLOT(removeFromModel(QGraphicsItem*)));
  connect(&scene, SIGNAL(addInstance(Point)), this, SLOT(addInstance(Point)));

  updater.init();
}

CompositionDraw::~CompositionDraw()
{
  composition.getSelfInstance()->unregisterObserver(this);
}

void CompositionDraw::removeFromModel(QGraphicsItem *item)
{
  updater.removeFromModel(item);
}

void CompositionDraw::addInstance(Point position)
{
  addInstance(position, updater.getComposition());
}

void CompositionDraw::widthChanged()
{
  //TODO reimplement
  //  updateSceneRect();
}

void CompositionDraw::heightChanged()
{
  //TODO reimplement
  //  updateSceneRect();
}

void CompositionDraw::updateSceneRect()
{
  scene.setSceneRect(selfInst.boundingRect() | selfInst.childrenBoundingRect());
}

