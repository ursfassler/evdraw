#include "GiInstancePort.hpp"

#include <core/component/InstanceAppearance.hpp>
#include <core/connection/ConnectionFactory.hpp>
#include "convert.hpp"

#include <QBrush>

#include <QDebug>

GiInstancePort::GiInstancePort(InstancePort *aModel, Sheet *aSheet, QGraphicsItem *parent) :
  QGraphicsRectItem(parent),
  model(aModel),
  sheet(aSheet),
  label(this)
{
  setBrush(QBrush(QColor::fromRgb(0xff, 0xfa, 0x99)));

  Point topLeft     = -InstanceAppearance::portDimension() / 2;
  Point bottomRight =  InstanceAppearance::portDimension() / 2;

  setRect(QRectF(puToScene(topLeft), puToScene(bottomRight)));
  setPos(puToScene(model->getOffset()));

  label.setText(QString::fromStdString(model->getCompPort()->getName()));
  label.setPos(-label.boundingRect().width()/2, -label.boundingRect().height()/2);
}

void GiInstancePort::mousePressEvent(QGraphicsSceneMouseEvent *)
{
}

void GiInstancePort::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
  event->accept();
  qDebug() << "click";

  PartialConnectionFromStart *con = ConnectionFactory::producePartialFromStart();
  model->getConnector().addPoint(&con->getStart());
  con->getEnd().setPosition(sceneToPu(event->scenePos()));
  sheet->setConnectionUnderConstruction(con);
}
