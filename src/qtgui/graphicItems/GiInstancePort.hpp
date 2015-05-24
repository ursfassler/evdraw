#ifndef GIINSTANCEPORT_HPP
#define GIINSTANCEPORT_HPP

#include <core/instance/InstancePort.hpp>

#include <QGraphicsRectItem>

class GiInstancePort : public QGraphicsRectItem
{
  public:
    explicit GiInstancePort(InstancePort *model, QGraphicsItem *parent);

  signals:

  public slots:

};

#endif // GIINSTANCEPORT_HPP
