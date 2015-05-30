#ifndef GIINSTANCEPORT_HPP
#define GIINSTANCEPORT_HPP

#include <core/instance/InstancePort.hpp>
#include <core/sheet/Sheet.hpp>

#include <QGraphicsRectItem>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsSceneMouseEvent>

class GiInstancePort : public QGraphicsRectItem
{
  public:
    explicit GiInstancePort(InstancePort *model, Sheet *sheet, QGraphicsItem *parent);

    InstancePort *getModel() const;

  signals:

  public slots:

  protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent * event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent * event);

  private:
    InstancePort *model;
    Sheet *sheet;
    QGraphicsSimpleTextItem label;

};

#endif // GIINSTANCEPORT_HPP
