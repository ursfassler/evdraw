#include "MainWindow.hpp"
#include "graphicItems/GiSegment.hpp"
#include "graphicItems/GiInstancePort.hpp"
#include "graphicItems/GiInstance.hpp"
#include "graphicItems/convert.hpp"

#include <core/Connection.hpp>
#include <core/ConnectionFactory.hpp>
#include <core/InstancePort.hpp>
#include <core/Component.hpp>
#include <core/Instance.hpp>
#include <core/InstanceAppearance.hpp>

#include <QApplication>

#include <cassert>

static void addConnectionToScene(Connection *con, QGraphicsScene &scene)
{
  for (HorizontalSegment *hs : con->getHorizontalSegment()) {
    GiSegment *ghs;
    if (hs->moveable()) {
      ghs = new GiHorizontalSegment(hs, nullptr);
    } else {
      ghs = new GiUnmoveableSegment(hs, nullptr);
    }
    scene.addItem(ghs);
  }
  for (VerticalSegment *hs : con->getVerticalSegment()) {
    assert(hs->moveable());
    GiVerticalSegment *ghs = new GiVerticalSegment(hs, nullptr);
    scene.addItem(ghs);
  }
}

static void addPortToScene(InstancePort *port, QGraphicsScene &scene)
{
  GiInstancePort *giPort = new GiInstancePort(port, nullptr);
  scene.addItem(giPort);
}

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  MainWindow w;

  InstancePort *portA = new InstancePort(sceneToPu(-50), sceneToPu(0), ConnectorSide::Right);
  InstancePort *portB = new InstancePort(sceneToPu(50), sceneToPu(0), ConnectorSide::Left);
  InstancePort *portC = new InstancePort(sceneToPu(50), sceneToPu(-30), ConnectorSide::Left);

  const std::vector<PaperUnit> line = {sceneToPu(-50), sceneToPu(0), sceneToPu(-20), sceneToPu(50), sceneToPu(20), sceneToPu(0), sceneToPu(50)};
  Connection *con1 = ConnectionFactory::produce(line);
  portA->addConnection(con1);
  portB->addConnection(con1);

  const std::vector<PaperUnit> line2 = {sceneToPu(-50), sceneToPu(0), sceneToPu(-20), sceneToPu(50), sceneToPu(20), sceneToPu(0), sceneToPu(50)};
  Connection *con2 = ConnectionFactory::produce(line2);
  portA->addConnection(con2);
  portC->addConnection(con2);

  Component *compA = new Component();
  Instance  *instA = new Instance(Point(0, 0), compA);
  InstanceAppearance *appA = new InstanceAppearance(compA);

  GiInstance *giinstA = new GiInstance(instA, appA, 0);

  QGraphicsScene &scene = w.getScene();

  addConnectionToScene(con1, scene);
  addConnectionToScene(con2, scene);
  addPortToScene(portA, scene);
  addPortToScene(portB, scene);
  addPortToScene(portC, scene);
  scene.addItem(giinstA);

  w.show();

  return a.exec();
}
