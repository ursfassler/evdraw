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
    void mouseMoveEvent(QGraphicsSceneMouseEvent * event);
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent * event);
    void absolutePositionChanged(const RelativePosition *sender);
    void offsetChanged(const RelativePosition *sender);

    void portAdded(AbstractPort *port);
    void portDeleted(AbstractPort *port);

  private:
    Instance * const model;
    Composition * const composition;
    QGraphicsSimpleTextItem instanceText;
    QGraphicsSimpleTextItem componentText;
    QPointF calcTextPos(unsigned index, const QRectF &boundingRect) const;
    QHash<AbstractPort*,GiInstancePort*> ports;

    void resize();
    void updatePosition();
    void addText();
    void addPorts(Composition *composition);
    void addPort(AbstractPort *port, Composition *composition);
};

#endif // GIINSTANCE_HPP
