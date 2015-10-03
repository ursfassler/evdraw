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
    QHash<IPort*,GiInstancePort*> ports;

    void resize();
    void updatePosition();
    void updateText();
    void addPorts(Composition *composition);
    void addPort(IPort *port, Composition *composition);

    void absolutePositionChanged(const RelativePosition *sender) override;
    void offsetChanged(const RelativePosition *sender) override;

    void portAdded(IPort *port) override;
    void portDeleted(IPort *port) override;
    void nameChanged(const IInstance *) override;
    void componentNameChanged(const IInstance *) override;
    void heightChanged() override;

};

#endif // GIINSTANCE_HPP
