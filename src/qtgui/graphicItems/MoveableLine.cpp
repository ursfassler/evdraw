// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "MoveableLine.hpp"

#include "convert.hpp"

MoveableLine::MoveableLine(QGraphicsItem *parent) :
  QGraphicsLineItem(parent)
{
}

void MoveableLine::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
  grabMouse();
  event->accept();
}

void MoveableLine::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
  ungrabMouse();
  event->accept();
}

void MoveableLine::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
  const auto end = sceneToPu( event->scenePos() );
  event->accept();
  moveTo(end);
}
