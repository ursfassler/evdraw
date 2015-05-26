#include "GiInstancePort.hpp"

#include <core/component/InstanceAppearance.hpp>
#include "convert.hpp"

#include <QBrush>

#include <QDebug>

GiInstancePort::GiInstancePort(InstancePort *model, Sheet *aSheet, QGraphicsItem *parent) :
  QGraphicsRectItem(parent),
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
  if (connection == nullptr) {
    event->accept();
    grabMouse();
    qDebug() << "click";

    connection = new Connection(Connection::Mode::BuildToEnd);
    sheet->addConnection(connection);
    xxx
  } else {
  }
}
