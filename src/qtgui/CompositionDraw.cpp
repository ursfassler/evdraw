// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "CompositionDraw.hpp"

#include "graphicItems/convert.hpp"

#include <core/component/InstanceAppearance.hpp>
#include <core/instance/InstanceFactory.hpp>
#include "graphicItems/convert.hpp"

CompositionDraw::CompositionDraw(Composition &aComposition, QWidget *parent) :
  QGraphicsView(parent),
  scene(this),
  updater(scene, aComposition),
  composition(aComposition)
{
  setScene(&scene);

  const qreal width = puToScene(composition.getSelfInstance()->getWidth());
  scene.setSceneRect(-width/2, 0, width, puToScene(composition.getSelfInstance()->getHeight()));
  scene.addRect(scene.sceneRect());

  QFont font("Sans", 0.6 * puToScene(InstanceAppearance::textHeight()));
  scene.setFont(font);

  connect(&scene, SIGNAL(removeFromModel(QGraphicsItem*)), this, SLOT(removeFromModel(QGraphicsItem*)));
  connect(&scene, SIGNAL(addInstance(Point)), this, SLOT(addInstance(Point)));

  updater.init();
}

void CompositionDraw::removeFromModel(QGraphicsItem *item)
{
  updater.removeFromModel(item);
}

void CompositionDraw::addInstance(Point position)
{
  addInstance(position, updater.getComposition());
}
