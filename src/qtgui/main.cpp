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

class SheetHandler : public SheetObserver
{
  public:
    SheetHandler(QGraphicsScene &aScene, Sheet &aSheet) :
      scene(aScene),
      sheet(aSheet)
    {
    }

    virtual void instanceAdded(Instance *instance)
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

    virtual void connectionAdded(Connection *connection)
    {
      for (HorizontalSegment *hs : connection->getHorizontalSegment()) {
        GiSegment *ghs;
        if (hs->moveable()) {
          ghs = new GiHorizontalSegment(hs, nullptr);
        } else {
          ghs = new GiUnmoveableSegment(hs, nullptr);
        }
        scene.addItem(ghs);
      }
      for (VerticalSegment *hs : connection->getVerticalSegment()) {
        assert(hs->moveable());
        GiVerticalSegment *ghs = new GiVerticalSegment(hs, nullptr);
        scene.addItem(ghs);
      }
    }


    virtual void addConnectionUnderConnstruction(PartialConnectionFromStart *connection){ (void)(connection); }
    virtual void abortConnectionUnderConnstruction(PartialConnectionFromStart *connection){ (void)(connection); }

  private:
    QGraphicsScene &scene;
    Sheet &sheet;


};

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

  SheetHandler sheetHandler(scene, sheet);
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
