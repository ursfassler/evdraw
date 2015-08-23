// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "CompositionScene.hpp"
#include "convert.hpp"

CompositionScene::CompositionScene(QObject *parent) :
  QGraphicsScene(parent)
{
}

void CompositionScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
  if (event->modifiers().testFlag(Qt::ControlModifier)) {
    QGraphicsItem * item = itemAt(event->scenePos(), QTransform());
    if (item) {
      removeFromModel(item);
    } else {
      addInstance(sceneToPu(event->scenePos()));
    }
    event->accept();
  } else {
    QGraphicsScene::mousePressEvent(event);
  }
}
