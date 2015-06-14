#include "CompositionToGuiUpdater.hpp"


CompositionToGuiUpdater::CompositionToGuiUpdater(QGraphicsScene &aScene, Composition &aSheet) :
  scene(aScene),
  composition(aSheet)
{
  composition.registerObserver(this);
}

CompositionToGuiUpdater::~CompositionToGuiUpdater()
{
  composition.unregisterObserver(this);
}

void CompositionToGuiUpdater::instanceAdded(Instance *instance)
{
  GiInstance *giinstA = new GiInstance(instance, 0);

  for (AbstractPort *port : instance->getPorts()) {
    InstancePort *ip = dynamic_cast<InstancePort*>(port);
    new GiInstancePort(ip, &composition, giinstA);
  }

  scene.addItem(giinstA);
}

void CompositionToGuiUpdater::connectionAdded(Connection *connection)
{
  addConnection(connection);
}

void CompositionToGuiUpdater::addConnectionUnderConstruction(Connection *connection)
{
  connCreate = new GiConnectionCreation(connection, &composition);
  scene.addItem(connCreate);
  connCreate->grabMouse();
  addConnection(connection);
  connection->registerObserver(this);


}

void CompositionToGuiUpdater::finishConnectionUnderConstruction(Connection *)
{
  assert(connCreate != nullptr);
  delete connCreate;
}

void CompositionToGuiUpdater::addVerticalSegment(const Connection *, VerticalSegment *segment)
{
  GiVerticalSegment *ghs = new GiVerticalSegment(segment, nullptr);
  scene.addItem(ghs);
}

void CompositionToGuiUpdater::addHorizontalSegment(const Connection *, HorizontalSegment *segment)
{
  GiSegment *ghs = new GiHorizontalSegment(segment, nullptr);
  scene.addItem(ghs);
}

void CompositionToGuiUpdater::addConnection(Connection *connection)
{
  for (HorizontalSegment *hs : connection->getHorizontalSegment()) {
    addHorizontalSegment(connection, hs);
  }
  for (VerticalSegment *hs : connection->getVerticalSegment()) {
    addVerticalSegment(connection, hs);
  }
}

void CompositionToGuiUpdater::init()
{
  for (Instance *inst : composition.getInstances()) {
    instanceAdded(inst);
  }
  for (Connection *conn : composition.getConnections()) {
    connectionAdded(conn);
  }
}
