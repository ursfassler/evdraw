#ifndef GIINSTANCE_HPP
#define GIINSTANCE_HPP

#include <core/instance/Instance.hpp>

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSimpleTextItem>

class GiInstance final : public QGraphicsRectItem, public PositionObserver
{
  public:
    GiInstance(Instance *aModel, QGraphicsItem *parent);
    ~GiInstance();

  protected:
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent * event);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent * event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent * event);
    virtual void notify(const RelativePosition *sender);

  private:
    Instance * const model;
    QGraphicsSimpleTextItem instanceText;
    QGraphicsSimpleTextItem componentText;
    QPointF calcTextPos(unsigned index, const QRectF &boundingRect) const;
};

#endif // GIINSTANCE_HPP
