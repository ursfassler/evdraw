// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef MOVEABLELINE_H
#define MOVEABLELINE_H

#include <QGraphicsLineItem>
#include <QGraphicsSceneMouseEvent>

#include <core/Point.hpp>

class MoveableLine :
    public QGraphicsLineItem
{
  public:
    MoveableLine(QGraphicsItem *parent);

  protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent * event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent * event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent * event) override;

    virtual void moveTo(const Point &pos) = 0;

};

#endif // MOVEABLELINE_H
