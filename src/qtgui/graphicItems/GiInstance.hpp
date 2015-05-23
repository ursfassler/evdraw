#ifndef GIINSTANCE_HPP
#define GIINSTANCE_HPP

#include <core/Instance.hpp>
#include <core/InstanceAppearance.hpp>

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

class GiInstance : public QGraphicsRectItem
{
  public:
    GiInstance(Instance *aModel, InstanceAppearance *aAppearance, QGraphicsItem *parent);

  protected:
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent * event);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent * event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent * event);

  private:
    Instance const * model;
    InstanceAppearance const * appearance;
};

#endif // GIINSTANCE_HPP
