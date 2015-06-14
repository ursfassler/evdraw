#include "MainWindow.hpp"
#include "graphicItems/GiSegment.hpp"
#include "graphicItems/GiInstancePort.hpp"
#include "graphicItems/GiInstance.hpp"
#include "graphicItems/convert.hpp"

#include <QApplication>

#include <cassert>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

//  Composition *composition = dynamic_cast<Composition*>(lib->getComponents().back()->getImplementation());
//  CompositionEditor *compEdit = openComposition(composition);
//  compEdit->show();

  MainWindow w;
  w.show();

  return a.exec();
}
