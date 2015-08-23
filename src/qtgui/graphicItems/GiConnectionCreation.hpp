// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef GICONNECTIONCREATION_HPP
#define GICONNECTIONCREATION_HPP

#include "GiInstancePort.hpp"

#include <core/connection/Connection.hpp>
#include <core/connection/DrawPort.hpp>
#include <core/implementation/Composition.hpp>

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

class GiConnectionCreation : public QGraphicsRectItem
{
  public:
    GiConnectionCreation(Connection *connection, Composition *sheet);
    ~GiConnectionCreation();

  protected:
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent * event);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent * event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent * event);

  private:
    DrawPort * const port;
    Connection * const connection;
    Composition * const sheet;

    GiInstancePort *filterPort(const QList<QGraphicsItem *> &list) const;
};

#endif // GICONNECTIONCREATION_HPP
