#include "GiInstance.hpp"

#include <core/component/InstanceAppearance.hpp>

#include "convert.hpp"

#include <QBrush>
#include <QFont>
#include <QRectF>

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
  componentText.setText(QString::fromStdString(model->getComponent()->getName()));
  instanceText.setPos(calcTextPos(0, instanceText.boundingRect()));
  componentText.setPos(calcTextPos(1, componentText.boundingRect()));
}

GiInstance::~GiInstance()
{
  model->unregisterObserver(this);
}

void GiInstance::notify(const Base *)
{
  setPos(puToScene(model->getOffset()));
}

QPointF GiInstance::calcTextPos(unsigned index, const QRectF &boundingRect) const
{
  const qreal x = -boundingRect.width()/2;
  const qreal offset = (0.5 + index) * puToScene(InstanceAppearance::textHeight());
  const qreal y = offset - boundingRect.height()/2;
  return QPointF(x,y);
}

void GiInstance::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
  model->setOffset(sceneToPu(event->scenePos() - event->lastPos()));
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
