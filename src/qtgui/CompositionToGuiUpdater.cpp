// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "CompositionToGuiUpdater.hpp"
#include <core/connection/ConnectionFactory.hpp>


CompositionToGuiUpdater::CompositionToGuiUpdater(QGraphicsScene &aScene, Composition &aComposition) :
  scene(aScene),
  composition(aComposition)
{
  composition.registerObserver(this);
  composition.getConnections().registerObserver(this);
  composition.getInstances().registerObserver(this);
}

CompositionToGuiUpdater::~CompositionToGuiUpdater()
{
  composition.getInstances().unregisterObserver(this);
  composition.getConnections().unregisterObserver(this);
  composition.unregisterObserver(this);
}

void CompositionToGuiUpdater::added(Instance *instance)
{
  GiInstance *giinstA = new GiInstance(instance, 0);
  instances.insert(instance, giinstA);
  scene.addItem(giinstA);

  connect(giinstA, SIGNAL(startConnection(InstancePort*,Point)), this, SLOT(startConnection(InstancePort*,Point)));
}

void CompositionToGuiUpdater::removed(Instance *instance)
{
  GiInstance *inst = instances.take(instance);
  delete inst;
}

void CompositionToGuiUpdater::added(Connection *connection)
{
  addConnection(connection);
}

void CompositionToGuiUpdater::removed(Connection *connection)
{
  ConnectionItem *item = connections.take(connection);
  delete item;
}

void CompositionToGuiUpdater::addConnectionUnderConstruction(Connection *connection)
{
  connCreate = new GiConnectionCreation(connection, &composition);
  scene.addItem(connCreate);
  connCreate->grabMouse();
  addConnection(connection);
}

void CompositionToGuiUpdater::finishConnectionUnderConstruction(Connection *connection)
{
  ConnectionItem *item = connections.take(connection);
  delete item;

  assert(connCreate != nullptr);
  delete connCreate;
}

void CompositionToGuiUpdater::addConnection(Connection *connection)
{
  ConnectionItem *item = new ConnectionItem(connection, scene);
  connections.insert(connection, item);
}

void CompositionToGuiUpdater::init()
{
  for (Instance *inst : composition.getInstances()) {
    added(inst);
  }
  for (Connection *conn : composition.getConnections()) {
    added(conn);
  }
}

void CompositionToGuiUpdater::removeFromModel(QGraphicsItem *item)
{
  Connection *connection = findConnectionOf(item);
  if (connection != nullptr) {
    composition.getConnections().remove(connection);
  }
}

Connection *CompositionToGuiUpdater::findConnectionOf(QGraphicsItem *item) const
{
  QHashIterator<Connection*,ConnectionItem*> i(connections);
  while (i.hasNext()) {
    i.next();
    if (i.value()->hasItem(item)) {
      return i.key();
    }
  }

  return nullptr;
}

Composition &CompositionToGuiUpdater::getComposition()
{
  return composition;
}

void CompositionToGuiUpdater::startConnection(InstancePort *port, const Point &pos)
{
  DrawPort *end = new DrawPort(pos);
  composition.startConnectionConstruction(port, end);
}




ConnectionItem::ConnectionItem(Connection *aConnection, QGraphicsScene &aScene) :
  connection(aConnection),
  scene(aScene)
{
  connection->registerObserver(this);

  for (HorizontalSegment *hs : connection->getHorizontalSegment()) {
    horizontalSegmentAdded(hs);
  }
  for (VerticalSegment *hs : connection->getVerticalSegment()) {
    verticalSegmentAdded(hs);
  }
}

ConnectionItem::~ConnectionItem()
{
  for (QGraphicsItem *itr : items) {
    scene.removeItem(itr);
    delete itr;
  }
  items.clear();

  connection->unregisterObserver(this);
}

bool ConnectionItem::hasItem(QGraphicsItem *item) const
{
  return items.contains(item);
}

void ConnectionItem::verticalSegmentAdded(VerticalSegment *segment)
{
  GiVerticalSegment *ghs = new GiVerticalSegment(segment, nullptr);
  scene.addItem(ghs);
  items.insert(ghs);
}

void ConnectionItem::horizontalSegmentAdded(HorizontalSegment *segment)
{
  GiHorizontalSegment *ghs = new GiHorizontalSegment(segment, nullptr);
  scene.addItem(ghs);
  items.insert(ghs);
}

