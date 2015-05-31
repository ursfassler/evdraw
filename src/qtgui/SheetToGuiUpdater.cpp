#include "SheetToGuiUpdater.hpp"


SheetToGuiUpdater::SheetToGuiUpdater(QGraphicsScene &aScene, Sheet &aSheet) :
  scene(aScene),
  sheet(aSheet)
{
}

void SheetToGuiUpdater::instanceAdded(Instance *instance)
{
  GiInstance *giinstA = new GiInstance(instance, 0);

  for (InstancePort *port : instance->getInput()) {
    new GiInstancePort(port, &sheet, giinstA);
  }
  for (InstancePort *port : instance->getOutput()) {
    new GiInstancePort(port, &sheet, giinstA);
  }

  scene.addItem(giinstA);
}

void SheetToGuiUpdater::connectionAdded(Connection *connection)
{
  addConnection(connection);
}

void SheetToGuiUpdater::addConnectionUnderConnstruction(Connection *connection)
{
  connCreate = new GiConnectionCreation(connection, &sheet);
  scene.addItem(connCreate);
  connCreate->grabMouse();
  addConnection(connection);
  connection->registerObserver(this);
}

void SheetToGuiUpdater::abortConnectionUnderConnstruction(Connection *connection)
{
  (void)(connection);
}

void SheetToGuiUpdater::addVerticalSegment(const Connection *, VerticalSegment *segment)
{
  GiVerticalSegment *ghs = new GiVerticalSegment(segment, nullptr);
  scene.addItem(ghs);
}

void SheetToGuiUpdater::addHorizontalSegment(const Connection *, HorizontalSegment *segment)
{
  GiSegment *ghs = new GiHorizontalSegment(segment, nullptr);
  scene.addItem(ghs);
}

void SheetToGuiUpdater::addConnection(Connection *connection)
{
  for (HorizontalSegment *hs : connection->getHorizontalSegment()) {
    addHorizontalSegment(connection, hs);
  }
  for (VerticalSegment *hs : connection->getVerticalSegment()) {
    //    assert(hs->moveable());
    addVerticalSegment(connection, hs);
  }
}
