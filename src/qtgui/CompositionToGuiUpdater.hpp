// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef COMPOSITIONTOGUIUPDATER_HPP
#define COMPOSITIONTOGUIUPDATER_HPP

#include "graphicItems/GiInstance.hpp"
#include "graphicItems/GiSegment.hpp"
#include "graphicItems/GiConnectionCreation.hpp"

#include <core/implementation/Composition.hpp>

#include <QGraphicsScene>
#include <QHash>

class ConnectionItem : public ConnectionObserver
{
  public:
    ConnectionItem(Connection *connection, QGraphicsScene &scene);
    ~ConnectionItem();

    bool hasItem(QGraphicsItem *item) const;

  protected:
    virtual void verticalSegmentAdded(VerticalSegment *segment);
    virtual void horizontalSegmentAdded(HorizontalSegment *segment);

  private:
    Connection * const connection;
    QGraphicsScene &scene;
    QSet<QGraphicsItem*> items;
};

class CompositionToGuiUpdater : public CompositionObserver
{
  public:
    CompositionToGuiUpdater(QGraphicsScene &aScene, Composition &aSheet);
    ~CompositionToGuiUpdater();

    virtual void instanceAdded(Instance *instance);
    virtual void instanceRemoved(Instance *instance);
    virtual void connectionAdded(Connection *connection);
    virtual void connectionRemoved(Connection *connection);
    virtual void addConnectionUnderConstruction(Connection *connection);
    virtual void finishConnectionUnderConstruction(Connection *connection);

    void init();

    void removeFromModel(QGraphicsItem *item);

    Composition &getComposition();

  private:
    QGraphicsScene &scene;
    Composition &composition;
    GiConnectionCreation *connCreate = nullptr;

    QHash<Connection*,ConnectionItem*> connections;
    QHash<Instance*,GiInstance*> instances;

    void addConnection(Connection *connection);
    Connection *findConnectionOf(QGraphicsItem *item) const;

};

#endif
