// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef GIINSTANCE_HPP
#define GIINSTANCE_HPP

#include "graphicItems/GiInstancePort.hpp"

#include <core/instance/Instance.hpp>

#include <QObject>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSimpleTextItem>
#include <QHash>

class GiInstance final :
    public QObject,
    public QGraphicsRectItem,
    private PositionObserver,
    private InstanceObserver,
    private ListObserver<InstancePort>
{
    Q_OBJECT

  public:
    GiInstance(Instance *aModel, QGraphicsItem *parent);
    ~GiInstance();

  signals:
    void startConnection(InstancePort *port, const Point &pos);

  protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent * event);
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent * event);

  private:
    Instance * const model;
    QGraphicsSimpleTextItem instanceText;
    QGraphicsSimpleTextItem componentText;
    QPointF calcTextPos(unsigned index, const QRectF &boundingRect) const;
    QHash<IPort*,GiInstancePort*> ports;

    void resize();
    void updatePosition();
    void updateText();
    void addPorts();
    void addPort(IPort *port);

    void absolutePositionChanged(const RelativePosition *sender) override;
    void offsetChanged(const RelativePosition *sender) override;

    void added(InstancePort *port) override;
    void removed(InstancePort *port) override;
    void nameChanged(const IInstance *) override;
    void componentNameChanged(const IInstance *) override;
    void heightChanged() override;

};

#endif // GIINSTANCE_HPP
