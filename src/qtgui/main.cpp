#include "MainWindow.hpp"
#include "graphicItems/GiSegment.hpp"
#include "graphicItems/GiInstancePort.hpp"
#include "graphicItems/GiInstance.hpp"
#include "graphicItems/convert.hpp"
#include "SheetToGuiUpdater.hpp"

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

static void loadSheet(Sheet &sheet, Component *comp)
{
  Instance *inst1 = InstanceFactory::produce(comp, "instance1", sceneToPu(QPointF(-150,0)));
  sheet.addInstance(inst1);
  Instance *inst2 = InstanceFactory::produce(comp, "instance2", sceneToPu(QPointF( 150,0)));
  sheet.addInstance(inst2);

  InstancePort *portA = inst1->getOutput()[0];
  InstancePort *portB = inst2->getInput()[0];
  InstancePort *portC = inst2->getInput()[1];

  const std::vector<PaperUnit> line = {sceneToPu(-50), sceneToPu(0), sceneToPu(-20), sceneToPu(50), sceneToPu(20), sceneToPu(0), sceneToPu(50)};
  Connection *con1 = ConnectionFactory::produce(line);
  portA->getConnector().addPoint(&con1->getStart());
  portB->getConnector().addPoint(&con1->getEnd());
  sheet.addConnection(con1);

  const std::vector<PaperUnit> line2 = {sceneToPu(-50), sceneToPu(0), sceneToPu(-20), sceneToPu(50), sceneToPu(20), sceneToPu(0), sceneToPu(50)};
  Connection *con2 = ConnectionFactory::produce(line2);
  portA->getConnector().addPoint(&con2->getStart());
  portC->getConnector().addPoint(&con2->getEnd());
  sheet.addConnection(con2);
}

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  Component *comp = ComponentFactory::produce("Component", {"in1", "in2"}, {"out1", "out2", "out3"});
  Sheet sheet;

  MainWindow *w = new MainWindow();
  QGraphicsScene &scene = w->getScene();

  SheetToGuiUpdater sheetHandler(scene, sheet);
  sheet.registerObserver(&sheetHandler);

  loadSheet(sheet, comp);

  QFont font("Sans", 0.6 * puToScene(InstanceAppearance::textHeight()));
  scene.setFont(font);

//  fillSceneFromSheet(scene, sheet);
  w->setMinimumSize(640, 480);
  w->show();

  int ret = a.exec();

  delete w;

  sheet.unregisterObserver(&sheetHandler);

  ComponentFactory::dispose(comp);

  return ret;
}
