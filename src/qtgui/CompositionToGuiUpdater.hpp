#ifndef COMPOSITIONTOGUIUPDATER_HPP
#define COMPOSITIONTOGUIUPDATER_HPP

#include "graphicItems/GiInstance.hpp"
#include "graphicItems/GiInstancePort.hpp"
#include "graphicItems/GiSegment.hpp"
#include "graphicItems/GiConnectionCreation.hpp"

#include <core/implementation/Composition.hpp>

#include <QGraphicsScene>
#include <QHash>

class CompositionToGuiUpdater : public CompositionObserver, public ConnectionObserver
{
  public:
    CompositionToGuiUpdater(QGraphicsScene &aScene, Composition &aSheet);
    ~CompositionToGuiUpdater();

    virtual void instanceAdded(Instance *instance);
    virtual void connectionAdded(Connection *connection);
    virtual void connectionRemoved(Connection *connection);
    virtual void addConnectionUnderConstruction(Connection *connection);
    virtual void finishConnectionUnderConstruction(Connection *connection);

    virtual void addVerticalSegment(Connection *parent, VerticalSegment *segment);
    virtual void addHorizontalSegment(Connection *parent, HorizontalSegment *segment);

    void init();

    void removeFromModel(QGraphicsItem *item);

    Composition &getComposition();

  private:
    QGraphicsScene &scene;
    Composition &composition;
    GiConnectionCreation *connCreate = nullptr;

    QHash<QGraphicsItem*, Connection*> connections;

    void addConnection(Connection *connection);



};

#endif
