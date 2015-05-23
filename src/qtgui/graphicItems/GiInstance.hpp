#ifndef GIINSTANCE_HPP
#define GIINSTANCE_HPP

#include <core/Instance.hpp>
#include <core/InstanceAppearance.hpp>

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

class GiInstance : public QGraphicsRectItem, public InstanceListener
{
  public:
    GiInstance(Instance *aModel, InstanceAppearance *aAppearance, QGraphicsItem *parent);
    ~GiInstance();

  protected:
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent * event);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent * event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent * event);
    virtual void positionChange(const Instance *sender);

  private:
    Instance * const model;
    InstanceAppearance const * appearance;
};

#endif // GIINSTANCE_HPP
