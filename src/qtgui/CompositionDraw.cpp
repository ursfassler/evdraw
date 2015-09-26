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

  ICompositionInstance *self = composition.getSelfInstance();

  const qreal width = puToScene(self->getWidth());
  scene.setSceneRect(-width/2, 0, width, puToScene(self->getHeight()));
  scene.addRect(scene.sceneRect());

  addPorts(self->getPorts());

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

void CompositionDraw::addPorts(const std::vector<InstancePort *> &ports)
{
  for (InstancePort *port : ports) {
    addPort(port);
  }
}

void CompositionDraw::addPort(InstancePort *port)
{
  InstancePort *ip = dynamic_cast<InstancePort*>(port);
  GiInstancePort *gipo = new GiInstancePort(ip, &composition, nullptr);
  scene.addItem(gipo);
//  ports[ip] = gipo;
}

