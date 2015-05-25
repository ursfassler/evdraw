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
#include <core/sheet/Sheet.hpp>

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

static void fillSceneFromSheet(QGraphicsScene &scene, const Sheet *sheet)
{
  for (Instance *instance : sheet->getInstances()) {
    addInstanceToScene(instance, scene);
  }
  for (Connection *connection : sheet->getConnections()) {
    addConnectionToScene(connection, scene);
  }
}

static Sheet* createSheet(Component *comp)
{
  Sheet *sheet = new Sheet();
  Instance *inst1 = InstanceFactory::produce(comp, "instance1", sceneToPu(QPointF(-150,0)));
  sheet->addInstance(inst1);
  Instance *inst2 = InstanceFactory::produce(comp, "instance2", sceneToPu(QPointF( 150,0)));
  sheet->addInstance(inst2);

  InstancePort *portA = inst1->getOutput()[0];
  InstancePort *portB = inst2->getInput()[0];
  InstancePort *portC = inst2->getInput()[1];

  const std::vector<PaperUnit> line = {sceneToPu(-50), sceneToPu(0), sceneToPu(-20), sceneToPu(50), sceneToPu(20), sceneToPu(0), sceneToPu(50)};
  Connection *con1 = ConnectionFactory::produce(line);
  portA->getConnector().addPoint(&con1->getStart());
  portB->getConnector().addPoint(&con1->getEnd());
  sheet->addConnection(con1);

  const std::vector<PaperUnit> line2 = {sceneToPu(-50), sceneToPu(0), sceneToPu(-20), sceneToPu(50), sceneToPu(20), sceneToPu(0), sceneToPu(50)};
  Connection *con2 = ConnectionFactory::produce(line2);
  portA->getConnector().addPoint(&con2->getStart());
  portC->getConnector().addPoint(&con2->getEnd());
  sheet->addConnection(con2);

  return sheet;
}

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  Component *comp = ComponentFactory::produce("Component", {"in1", "in2"}, {"out1", "out2", "out3"});
  Sheet *sheet = createSheet(comp);

  MainWindow *w = new MainWindow();
  QGraphicsScene &scene = w->getScene();
  QFont font("Sans", 0.6 * puToScene(InstanceAppearance::textHeight()));
  scene.setFont(font);
  fillSceneFromSheet(scene, sheet);
  w->setMinimumSize(640, 480);
  w->show();

  int ret = a.exec();

  delete w;

  delete sheet;
  ComponentFactory::dispose(comp);

  return ret;
}
