// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef GIINSTANCEPORT_HPP
#define GIINSTANCEPORT_HPP

#include <core/instance/InstancePort.hpp>

#include <QObject>
#include <QGraphicsRectItem>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsSceneMouseEvent>

class GiInstancePort :
    public QObject,
    public QGraphicsRectItem,
    protected PositionObserver,
    protected InstancePortObserver
{
    Q_OBJECT

  public:
    explicit GiInstancePort(InstancePort *model, QGraphicsItem *parent);
    ~GiInstancePort();

    InstancePort *getModel() const;

  signals:
    void startConnection(InstancePort *port, const Point &pos);

  public slots:

  protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent * event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent * event);

    virtual void absolutePositionChanged(const RelativePosition *sender);
    virtual void offsetChanged(const RelativePosition *sender);

    virtual void nameChanged(const std::string &name);

  private:
    InstancePort *model;
    QGraphicsSimpleTextItem label;

    void setDisplayName(QString name);

};

#endif // GIINSTANCEPORT_HPP
