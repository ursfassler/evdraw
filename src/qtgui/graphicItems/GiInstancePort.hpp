#ifndef GIINSTANCEPORT_HPP
#define GIINSTANCEPORT_HPP

#include <core/instance/InstancePort.hpp>

#include <QGraphicsRectItem>
#include <QGraphicsSimpleTextItem>

class GiInstancePort : public QGraphicsRectItem
{
  public:
    explicit GiInstancePort(InstancePort *model, QGraphicsItem *parent);

  signals:

  public slots:

  private:
    QGraphicsSimpleTextItem label;

};

#endif // GIINSTANCEPORT_HPP
