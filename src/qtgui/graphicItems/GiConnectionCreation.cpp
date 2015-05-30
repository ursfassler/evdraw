#include "GiConnectionCreation.hpp"

#include "convert.hpp"

#include <core/connection/ConnectionFactory.hpp>

#include <QGraphicsScene>

#include <QDebug>

GiConnectionCreation::GiConnectionCreation(ConstructionConnection *aConnection, Sheet *aSheet) :
  connection(aConnection),
  sheet(aSheet)
{
  setRect(-5,-5,10,10);
  setPos(puToScene(connection->getLeaf()->getPosition()));
  grabMouse();
}

GiConnectionCreation::~GiConnectionCreation()
{
  ungrabMouse();
}

void GiConnectionCreation::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
  connection->getLeaf()->setPosition(sceneToPu(event->scenePos()));
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
    connection->addSegment();
  } else {
    Connection *fincon = ConnectionFactory::produce(*connection);
    sheet->getRootPort()->getConnector().addPoint(fincon->getStart());
    port->getModel()->getConnector().addPoint(fincon->getEnd());
    sheet->addConnection(fincon);

#error When a connection is removed, notify connector about removed points

    sheet->removeConnectionUnderConstruction();
    ConnectionFactory::dispose(connection);
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
