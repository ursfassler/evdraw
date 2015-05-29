#include "GiConnectionCreation.hpp"

#include "convert.hpp"

GiConnectionCreation::GiConnectionCreation(PartialConnectionFromStart *aConnection) :
  connection(aConnection)
{
  setRect(-5,-5,10,10);
  setPos(puToScene(connection->getEnd().getPosition()));
  grabMouse();
}

GiConnectionCreation::~GiConnectionCreation()
{
  ungrabMouse();
}

void GiConnectionCreation::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
  connection->getEnd().setPosition(sceneToPu(event->scenePos()));
  setPos(event->scenePos());
  event->accept();
}

void GiConnectionCreation::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
  event->accept();
}

void GiConnectionCreation::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
  connection->addSegment();
  event->accept();
}
