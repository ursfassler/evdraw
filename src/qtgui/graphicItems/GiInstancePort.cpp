#include "GiInstancePort.hpp"

#include <core/component/InstanceAppearance.hpp>
#include "convert.hpp"

GiInstancePort::GiInstancePort(InstancePort *model, QGraphicsItem *parent) :
  QGraphicsRectItem(parent)
{
  Point topLeft     = -InstanceAppearance::portDimension() / 2;
  Point bottomRight =  InstanceAppearance::portDimension() / 2;

  setRect(QRectF(puToScene(topLeft), puToScene(bottomRight)));
  setPos(puToScene(model->getOffset()));
}
