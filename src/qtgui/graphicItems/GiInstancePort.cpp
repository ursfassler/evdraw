#include "GiInstancePort.hpp"

#include "convert.hpp"

GiInstancePort::GiInstancePort(InstancePort *model, QGraphicsItem *parent) :
  QGraphicsRectItem(parent)
{
  PaperUnit xofs;
  if (model->getConnectorSide() == InstancePort::ConnectorSide::Right) {
    xofs = - 2*model->getHeight();
  } else {
    xofs = 0;
  }
  qreal x = puToScene(model->getX() + xofs);
  qreal w = puToScene(2*model->getHeight());
  qreal y = puToScene(model->getY() - model->getHeight()/2);
  qreal h = puToScene(model->getHeight());

  setRect(x, y, w, h);
}
