#ifndef SHEETTOGUIUPDATER_HPP
#define SHEETTOGUIUPDATER_HPP

#include "graphicItems/GiInstance.hpp"
#include "graphicItems/GiInstancePort.hpp"
#include "graphicItems/GiSegment.hpp"
#include "graphicItems/GiConnectionCreation.hpp"

#include <core/implementation/Composition.hpp>

#include <QGraphicsScene>

class SheetToGuiUpdater : public CompositionObserver, public ConnectionObserver
{
  public:
    SheetToGuiUpdater(QGraphicsScene &aScene, Composition &aSheet);

    virtual void instanceAdded(Instance *instance);
    virtual void connectionAdded(Connection *connection);
    virtual void addConnectionUnderConstruction(Connection *connection);
    virtual void finishConnectionUnderConstruction(Connection *connection);

    virtual void addVerticalSegment(const Connection *parent, VerticalSegment *segment);
    virtual void addHorizontalSegment(const Connection *parent, HorizontalSegment *segment);

    void init();

  private:
    QGraphicsScene &scene;
    Composition &sheet;
    GiConnectionCreation *connCreate = nullptr;

    void addConnection(Connection *connection);


};

#endif // SHEETTOGUIUPDATER_HPP
