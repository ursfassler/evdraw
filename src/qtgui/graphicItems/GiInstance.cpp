#include "GiInstance.hpp"

#include "convert.hpp"

#include <QBrush>

GiInstance::GiInstance(Instance *aModel, InstanceAppearance *aAppearance, QGraphicsItem *parent) :
  QGraphicsRectItem(parent),
  model(aModel),
  appearance(aAppearance)
{
  model->addListener(this);
  setBrush(QBrush(QColor::fromRgb(0xf2, 0xf2, 0xff)));

  qreal x = puToScene(-appearance->width() / 2);
  qreal w = puToScene(appearance->width());
  qreal y = puToScene(0);
  qreal h = puToScene(appearance->height());

  setRect(x, y, w, h);
  setPos(puToScene(model->getPosition()));
}

GiInstance::~GiInstance()
{
  model->removeListener(this);
}

void GiInstance::positionChange(const Instance *)
{
  setPos(puToScene(model->getPosition()));
}

void GiInstance::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
  model->setPosition(sceneToPu(event->scenePos()));
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
