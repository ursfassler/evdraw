#include "GiInstancePort.hpp"

#include "GiConnectionCreation.hpp"

#include <core/component/InstanceAppearance.hpp>
#include <core/connection/ConnectionFactory.hpp>
#include <core/connection/DrawPort.hpp>
#include "convert.hpp"

#include <QBrush>

GiInstancePort::GiInstancePort(InstancePort *aModel, Composition *aSheet, QGraphicsItem *parent) :
  QGraphicsRectItem(parent),
  model(aModel),
  sheet(aSheet),
  label(this)
{
  model->registerObserver(this);

  setBrush(QBrush(QColor::fromRgb(0xff, 0xfa, 0x99)));

  Point topLeft     = -InstanceAppearance::portDimension() / 2;
  Point bottomRight =  InstanceAppearance::portDimension() / 2;

  setRect(QRectF(puToScene(topLeft), puToScene(bottomRight)));
  setPos(puToScene(model->getOffset()));

  label.setText(QString::fromStdString(model->getCompPort()->getName()));
  label.setPos(-label.boundingRect().width()/2, -label.boundingRect().height()/2);
}

GiInstancePort::~GiInstancePort()
{
  model->unregisterObserver(this);
}

InstancePort *GiInstancePort::getModel() const
{
  return model;
}

void GiInstancePort::mousePressEvent(QGraphicsSceneMouseEvent *)
{
}

void GiInstancePort::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
  event->accept();
  DrawPort *end = new DrawPort(sceneToPu(event->scenePos()));
  sheet->startConnectionConstruction(model, end);
}

void GiInstancePort::absolutePositionChanged(const RelativePosition *sender)
{

}

void GiInstancePort::offsetChanged(const RelativePosition *sender)
{
  setPos(puToScene(model->getOffset()));
}
