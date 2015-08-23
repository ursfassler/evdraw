// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "GiSegment.hpp"

#include "convert.hpp"

#include <QPen>
#include <QCursor>
#include <QDebug>

GiSegment::GiSegment(Segment *model, QGraphicsItem *parent) :
  QGraphicsLineItem(parent)
{
  setPen(QPen(QBrush(Qt::SolidPattern), 2));
  updatePosition(model);
}

GiSegment::~GiSegment()
{
}

void GiSegment::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
  event->accept();
}

void GiSegment::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
  grabMouse();
  event->accept();
}

void GiSegment::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
  ungrabMouse();
  event->accept();
}

void GiSegment::positionChanged(const Segment *)
{
  updatePosition(getModel());
}

void GiSegment::updatePosition(Segment *model)
{
  QPointF start = puToScene(model->getStart()->getAbsolutePosition());
  QPointF end = puToScene(model->getEnd()->getAbsolutePosition());

  setLine(QLineF(start, end));
}


GiHorizontalSegment::GiHorizontalSegment(HorizontalSegment *aModel, QGraphicsItem *parent) :
  GiSegment(aModel, parent),
  model(aModel)
{
  if (model->moveable()) {
    setCursor(QCursor(Qt::SizeVerCursor));
  }
  model->registerObserver(this);
}

GiHorizontalSegment::~GiHorizontalSegment()
{
  model->unregisterObserver(this);
}

void GiHorizontalSegment::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
  const PaperUnit end = sceneToPu( event->scenePos().y() );
  model->moveToY(end);
  GiSegment::mouseMoveEvent(event);
}

Segment *GiHorizontalSegment::getModel()
{
  return model;
}



GiVerticalSegment::GiVerticalSegment(VerticalSegment *aModel, QGraphicsItem *parent) :
  GiSegment(aModel, parent),
  model(aModel)
{
  if (model->moveable()) {
    setCursor(QCursor(Qt::SizeHorCursor));
  }
  model->registerObserver(this);
}

GiVerticalSegment::~GiVerticalSegment()
{
  model->unregisterObserver(this);
}

void GiVerticalSegment::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
  const PaperUnit end = sceneToPu( event->scenePos().x() );
  model->moveToX(end);
  GiSegment::mouseMoveEvent(event);
}

Segment *GiVerticalSegment::getModel()
{
  return model;
}
