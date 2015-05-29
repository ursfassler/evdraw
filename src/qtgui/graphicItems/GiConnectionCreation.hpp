#ifndef GICONNECTIONCREATION_HPP
#define GICONNECTIONCREATION_HPP

#include <core/connection/Connection.hpp>

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

class GiConnectionCreation : public QGraphicsRectItem
{
  public:
    GiConnectionCreation(PartialConnectionFromStart *connection);
    ~GiConnectionCreation();

  protected:
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent * event);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent * event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent * event);

  private:
    PartialConnectionFromStart * const connection;
};

#endif // GICONNECTIONCREATION_HPP
