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
    virtual void addConnectionUnderConnstruction(Connection *connection);
    virtual void abortConnectionUnderConnstruction(Connection *connection);

    virtual void addVerticalSegment(const Connection *parent, VerticalSegment *segment);
    virtual void addHorizontalSegment(const Connection *parent, HorizontalSegment *segment);

  private:
    QGraphicsScene &scene;
    Sheet &sheet;
    GiConnectionCreation *connCreate = nullptr;

    void addConnection(Connection *connection);


};

#endif // SHEETTOGUIUPDATER_HPP
