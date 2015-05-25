#include "GiInstance.hpp"

#include <core/component/InstanceAppearance.hpp>

#include "convert.hpp"

#include <QBrush>

GiInstance::GiInstance(Instance *aModel, QGraphicsItem *parent) :
  QGraphicsRectItem(parent),
  model(aModel),
  instanceText(this),
  componentText(this)
{
  model->registerObserver(this);
  setBrush(QBrush(QColor::fromRgb(0xf2, 0xf2, 0xff)));

  qreal x = puToScene(-InstanceAppearance::width() / 2);
  qreal w = puToScene(InstanceAppearance::width());
  qreal y = puToScene(0);
  qreal h = puToScene(InstanceAppearance::height(*model->getComponent()));

  setRect(x, y, w, h);
  setPos(puToScene(model->getOffset()));

  instanceText.setText(QString::fromStdString(model->getName()));
  instanceText.setPos(-instanceText.boundingRect().width()/2, 0);
  componentText.setText(QString::fromStdString(model->getComponent()->getName()));
  componentText.setPos(-componentText.boundingRect().width()/2, instanceText.boundingRect().height());
}

GiInstance::~GiInstance()
{
  model->unregisterObserver(this);
}

void GiInstance::notify(const Base *)
{
  setPos(puToScene(model->getOffset()));
}

void GiInstance::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
  model->setOffset(sceneToPu(event->scenePos()));
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
