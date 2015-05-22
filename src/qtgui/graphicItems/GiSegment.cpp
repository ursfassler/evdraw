#include "GiSegment.hpp"

#include "convert.hpp"

#include <QPen>
#include <QDebug>

GiSegment::GiSegment(Segment *model, QGraphicsItem *parent) :
  QGraphicsLineItem(parent)
{
  setPen(QPen(QBrush(Qt::SolidPattern), 2));
  model->addListener(this);
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

void GiSegment::positionChange(Segment *)
{
  updatePosition(getModel());
}

void GiSegment::updatePosition(Segment *model)
{
  qreal x1 = puToScene(model->getStart()->getX());
  qreal y1 = puToScene(model->getStart()->getY());
  qreal x2 = puToScene(model->getEnd()->getX());
  qreal y2 = puToScene(model->getEnd()->getY());

  setLine(x1, y1, x2, y2);
}


GiHorizontalSegment::GiHorizontalSegment(HorizontalSegment *aModel, QGraphicsItem *parent) :
  GiSegment(aModel, parent),
  model(aModel)
{
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


GiUnmoveableSegment::GiUnmoveableSegment(Segment *aModel, QGraphicsItem *parent) :
  GiSegment(aModel, parent),
  model(aModel)
{
}

Segment *GiUnmoveableSegment::getModel()
{
  return model;
}
