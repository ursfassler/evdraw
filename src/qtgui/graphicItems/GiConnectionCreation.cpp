// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "GiConnectionCreation.hpp"

#include "convert.hpp"

#include <core/connection/ConnectionFactory.hpp>

#include <QGraphicsScene>

#include <QDebug>

GiConnectionCreation::GiConnectionCreation(Connection *aConnection, Composition *aSheet) :
  port(dynamic_cast<DrawPort*>(aConnection->getEndPort())),
  connection(aConnection),
  sheet(aSheet)
{
  setRect(-5,-5,10,10);
  setPos(puToScene(port->getAbsolutePosition()));
  grabMouse();
}

GiConnectionCreation::~GiConnectionCreation()
{
  ungrabMouse();
}

void GiConnectionCreation::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
  port->setAbsolutePosition(sceneToPu(event->scenePos()));
  setPos(event->scenePos());
  event->accept();
}

void GiConnectionCreation::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
  event->accept();
}

void GiConnectionCreation::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
  event->accept();
  QList<QGraphicsItem *> items = scene()->items(event->scenePos());
  GiInstancePort *port = filterPort(items);
  if (port == nullptr) {
    connection->insertSegmentAtEnd();
  } else {
    sheet->finishConnectionConstruction(port->getModel());
  }
}

GiInstancePort *GiConnectionCreation::filterPort(const QList<QGraphicsItem *> &list) const
{
  for (QGraphicsItem *item : list) {
    GiInstancePort *port = dynamic_cast<GiInstancePort*>(item);
    if (port != nullptr) {
      return port;
    }
  }

  return nullptr;
}
