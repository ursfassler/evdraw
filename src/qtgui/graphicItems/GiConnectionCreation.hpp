#ifndef GICONNECTIONCREATION_HPP
#define GICONNECTIONCREATION_HPP

#include "GiInstancePort.hpp"

#include <core/connection/Connection.hpp>
#include <core/sheet/Sheet.hpp>

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

class GiConnectionCreation : public QGraphicsRectItem
{
  public:
    GiConnectionCreation(Connection *connection, Sheet *sheet);
    ~GiConnectionCreation();

  protected:
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent * event);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent * event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent * event);

  private:
    Connection * const connection;
    Sheet * const sheet;

    GiInstancePort *filterPort(const QList<QGraphicsItem *> &list) const;
};

#endif // GICONNECTIONCREATION_HPP
