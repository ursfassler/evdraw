#include "GiInstance.hpp"

#include "convert.hpp"

#include <QBrush>

GiInstance::GiInstance(Instance *aModel, InstanceAppearance *aAppearance, QGraphicsItem *parent) :
  QGraphicsRectItem(parent),
  model(aModel),
  appearance(aAppearance)
{
  setBrush(QBrush(QColor::fromRgb(0xf2, 0xf2, 0xff)));

  qreal x = puToScene(-appearance->width() / 2);
  qreal w = puToScene(appearance->width());
  qreal y = puToScene(0);
  qreal h = puToScene(appearance->height());

  setRect(x, y, w, h);
  setPos(puToScene(model->getX()), puToScene(model->getY()));
}

void GiInstance::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
  setPos(event->scenePos());
  event->accept();
}

void GiInstance::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
  grabMouse();
  event->accept();
}

void GiInstance::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
  ungrabMouse();
  event->accept();
}
