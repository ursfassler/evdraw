#include "GiConnectionCreation.hpp"

#include "convert.hpp"

#include <core/connection/ConnectionFactory.hpp>

#include <QGraphicsScene>

#include <QDebug>

GiConnectionCreation::GiConnectionCreation(Connection *aConnection, Sheet *aSheet) :
  connection(aConnection),
  sheet(aSheet)
{
  setRect(-5,-5,10,10);
  setPos(puToScene(connection->getEnd()->getPosition()));
  grabMouse();
}

GiConnectionCreation::~GiConnectionCreation()
{
  ungrabMouse();
}

void GiConnectionCreation::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
  connection->getEnd()->setPosition(sceneToPu(event->scenePos()));
  setPos(event->scenePos());
  event->accept();
}

void GiConnectionCreation::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
  event->accept();
}

void GiConnectionCreation::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
  QList<QGraphicsItem *> items = scene()->items(event->scenePos());
  GiInstancePort *port = filterPort(items);
  if (port == nullptr) {
    connection->insertSegmentAtEnd();
  } else {
#warning use something like finishConnectionConstruction
    port->getModel()->getConnector().addPoint(connection->getEnd());
    sheet->addConnection(connection);
    sheet->removeConnectionUnderConstruction();
    ungrabMouse();
  }
  event->accept();
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
