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
#include <core/implementation/Composition.hpp>
#include <file/XmlReader.hpp>

#include <QApplication>

#include <cassert>

static Library *loadLibrary()
{
  const std::string xml =
  "<evdraw>"
  "  <component name=\"Component\">"
  "    <slot name=\"in1\" />"
  "    <slot name=\"in2\" />"
  "    <signal name=\"out1\" />"
  "    <signal name=\"out2\" />"
  "    <signal name=\"out3\" />"
  "  </component>"
  "  <component name=\"draw\">"
  "    <composition>"
  "      <instance name=\"instance1\" component=\"Component\" x=\"-150000\" y=\"0\" >"
  "      <instance name=\"instance2\" component=\"Component\" x=\"150000\" y=\"0\">"
  "      <connection path=\"20000\">"
  "        <instanceport instance=\"instance1\" port=\"out1\" />"
  "        <instanceport instance=\"instance2\" port=\"in1\" />"
  "      </connection>"
  "      <connection path=\"-20000\">"
  "        <instanceport instance=\"instance1\" port=\"out1\" />"
  "        <instanceport instance=\"instance2\" port=\"in2\" />"
  "      </connection>"
  "    </composition>"
  "  </component>"
  "</evdraw>";

  return XmlReader::parse(xml);
}

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  Library *lib = loadLibrary();
  Composition *sheet = dynamic_cast<Composition*>(lib->getComponents().back()->getImplementation());

  MainWindow *w = new MainWindow();
  QGraphicsScene &scene = w->getScene();

  SheetToGuiUpdater sheetHandler(scene, *sheet);
  sheet->registerObserver(&sheetHandler);

  sheetHandler.init();

  QFont font("Sans", 0.6 * puToScene(InstanceAppearance::textHeight()));
  scene.setFont(font);

  w->setMinimumSize(640, 480);
  w->show();

  int ret = a.exec();

  delete w;

  sheet->unregisterObserver(&sheetHandler);

  delete lib;

  return ret;
}
