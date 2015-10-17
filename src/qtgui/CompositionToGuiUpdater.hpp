// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef COMPOSITIONTOGUIUPDATER_HPP
#define COMPOSITIONTOGUIUPDATER_HPP

#include "graphicItems/GiInstance.hpp"
#include "graphicItems/GiSegment.hpp"
#include "graphicItems/GiConnectionCreation.hpp"

#include <core/implementation/Composition.hpp>

#include <QObject>
#include <QGraphicsScene>
#include <QHash>

class ConnectionItem final :
    private ConnectionObserver
{
  public:
    ConnectionItem(Connection *connection, QGraphicsScene &scene);
    ~ConnectionItem();

    bool hasItem(QGraphicsItem *item) const;

  private:
    Connection * const connection;
    QGraphicsScene &scene;
    QSet<QGraphicsItem*> items;

    void verticalSegmentAdded(VerticalSegment *segment) override;
    void horizontalSegmentAdded(HorizontalSegment *segment) override;
};

class CompositionToGuiUpdater :
    public QObject,
    private CompositionObserver,
    private ListObserver<Instance>,
    private ListObserver<Connection>
{
    Q_OBJECT

  public:
    CompositionToGuiUpdater(QGraphicsScene &scene, Composition &composition);
    ~CompositionToGuiUpdater();

    void init();

    void removeFromModel(QGraphicsItem *item);

    Composition &getComposition();

  private slots:
    void startConnection(InstancePort *port, const Point &pos);

  private:
    QGraphicsScene &scene;
    Composition &composition;
    GiConnectionCreation *connCreate = nullptr;

    QHash<Connection*,ConnectionItem*> connections;
    QHash<Instance*,GiInstance*> instances;

    void addConnection(Connection *connection);
    Connection *findConnectionOf(QGraphicsItem *item) const;

    void added(Instance *instance) override;
    void removed(Instance *instance) override;
    void added(Connection *connection) override;
    void removed(Connection *connection) override;
    void addConnectionUnderConstruction(Connection *connection) override;
    void finishConnectionUnderConstruction(Connection *connection) override;


};

#endif
