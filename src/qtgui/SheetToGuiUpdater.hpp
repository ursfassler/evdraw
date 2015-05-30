#ifndef SHEETTOGUIUPDATER_HPP
#define SHEETTOGUIUPDATER_HPP

#include "graphicItems/GiInstance.hpp"
#include "graphicItems/GiInstancePort.hpp"
#include "graphicItems/GiSegment.hpp"
#include "graphicItems/GiConnectionCreation.hpp"

#include <core/sheet/Sheet.hpp>

#include <QGraphicsScene>

class SheetToGuiUpdater : public SheetObserver, public ConnectionObserver
{
  public:
    SheetToGuiUpdater(QGraphicsScene &aScene, Sheet &aSheet);

    virtual void instanceAdded(Instance *instance);
    virtual void connectionAdded(Connection *connection);
    virtual void addConnectionUnderConnstruction(ConstructionConnection *connection);
    virtual void abortConnectionUnderConnstruction(ConstructionConnection *connection);

    virtual void addVerticalSegment(const ConnectionBase *parent, VerticalSegment *segment);
    virtual void addHorizontalSegment(const ConnectionBase *parent, HorizontalSegment *segment);

  private:
    QGraphicsScene &scene;
    Sheet &sheet;
    GiConnectionCreation *connCreate = nullptr;

    void addConnection(ConnectionBase *connection);


};

#endif // SHEETTOGUIUPDATER_HPP
