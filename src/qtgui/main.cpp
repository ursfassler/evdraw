#include "MainWindow.hpp"
#include "graphicItems/GiSegment.hpp"
#include "graphicItems/GiInstancePort.hpp"
#include "graphicItems/GiInstance.hpp"
#include "graphicItems/convert.hpp"

#include <core/connection/Connection.hpp>
#include <core/connection/ConnectionFactory.hpp>
#include <core/component/Component.hpp>
#include <core/component/InstanceAppearance.hpp>
#include <core/component/ComponentFactory.hpp>
#include <core/instance/InstancePort.hpp>
#include <core/instance/Instance.hpp>
#include <core/instance/InstanceFactory.hpp>

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

static void addInstanceToScene(Instance *instance, QGraphicsScene &scene)
{
  GiInstance *giinstA = new GiInstance(instance, 0);

  for (InstancePort *port : instance->getInput()) {
    new GiInstancePort(port, giinstA);
  }
  for (InstancePort *port : instance->getOutput()) {
    new GiInstancePort(port, giinstA);
  }

  scene.addItem(giinstA);
}

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  Component *comp = ComponentFactory::produce("Component", {"in1", "in2"}, {"out1", "out2", "out3"});
  Instance *inst1 = InstanceFactory::produce(comp, "instance1", sceneToPu(QPointF(-150,0)));
  Instance *inst2 = InstanceFactory::produce(comp, "instance2", sceneToPu(QPointF( 150,0)));

  InstancePort *portA = inst1->getOutput()[0];
  InstancePort *portB = inst2->getInput()[0];
  InstancePort *portC = inst2->getInput()[1];

  const std::vector<PaperUnit> line = {sceneToPu(-50), sceneToPu(0), sceneToPu(-20), sceneToPu(50), sceneToPu(20), sceneToPu(0), sceneToPu(50)};
  Connection *con1 = ConnectionFactory::produce(line);
  portA->getConnector().addPoint(&con1->getStart());
  portB->getConnector().addPoint(&con1->getEnd());

  const std::vector<PaperUnit> line2 = {sceneToPu(-50), sceneToPu(0), sceneToPu(-20), sceneToPu(50), sceneToPu(20), sceneToPu(0), sceneToPu(50)};
  Connection *con2 = ConnectionFactory::produce(line2);
  portA->getConnector().addPoint(&con2->getStart());
  portC->getConnector().addPoint(&con2->getEnd());

  QFont font("Sans", 0.6 * puToScene(InstanceAppearance::textHeight()));

  MainWindow w;
  QGraphicsScene &scene = w.getScene();
  scene.setFont(font);
  addInstanceToScene(inst1, scene);
  addInstanceToScene(inst2, scene);
  addConnectionToScene(con1, scene);
  addConnectionToScene(con2, scene);

  w.setMinimumSize(640, 480);
  w.show();

  return a.exec();
}
