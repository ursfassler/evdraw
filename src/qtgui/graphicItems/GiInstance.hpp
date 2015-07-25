#ifndef GIINSTANCE_HPP
#define GIINSTANCE_HPP

#include "graphicItems/GiInstancePort.hpp"

#include <core/instance/Instance.hpp>

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSimpleTextItem>
#include <QHash>

class GiInstance final : public QGraphicsRectItem, public PositionObserver, public InstanceObserver
{
  public:
    GiInstance(Instance *aModel, Composition *composition, QGraphicsItem *parent);
    ~GiInstance();

  protected:
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent * event);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent * event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent * event);
    virtual void absolutePositionChanged(const RelativePosition *sender);
    virtual void offsetChanged(const RelativePosition *sender);
    virtual void portDeleted(AbstractPort *port);

  private:
    Instance * const model;
    QGraphicsSimpleTextItem instanceText;
    QGraphicsSimpleTextItem componentText;
    QPointF calcTextPos(unsigned index, const QRectF &boundingRect) const;
    QHash<AbstractPort*,GiInstancePort*> ports;

    void resize();
    void updatePosition();
    void addText();
    void addPorts(Composition *composition);
};

#endif // GIINSTANCE_HPP
