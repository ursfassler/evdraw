// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef GIINSTANCE_HPP
#define GIINSTANCE_HPP

#include "graphicItems/GiInstancePort.hpp"

#include <core/instance/Instance.hpp>

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSimpleTextItem>
#include <QHash>

class GiInstance final :
    public QGraphicsRectItem,
    private PositionObserver,
    private InstanceObserver
{
  public:
    GiInstance(Instance *aModel, Composition *composition, QGraphicsItem *parent);
    ~GiInstance();

  protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent * event);
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent * event);

  private:
    Instance * const model;
    Composition * const composition;
    QGraphicsSimpleTextItem instanceText;
    QGraphicsSimpleTextItem componentText;
    QPointF calcTextPos(unsigned index, const QRectF &boundingRect) const;
    QHash<InstancePort*,GiInstancePort*> ports;

    void resize();
    void updatePosition();
    void updateText();
    void addPorts(Composition *composition);
    void addPort(InstancePort *port, Composition *composition);

    void absolutePositionChanged(const RelativePosition *sender);
    void offsetChanged(const RelativePosition *sender);

    void portAdded(InstancePort *port);
    void portDeleted(InstancePort *port);
    void nameChanged(const Instance *);

};

#endif // GIINSTANCE_HPP
