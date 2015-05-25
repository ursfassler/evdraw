#include "GiInstancePort.hpp"

#include <core/component/InstanceAppearance.hpp>
#include "convert.hpp"

#include <QBrush>

GiInstancePort::GiInstancePort(InstancePort *model, QGraphicsItem *parent) :
  QGraphicsRectItem(parent),
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
