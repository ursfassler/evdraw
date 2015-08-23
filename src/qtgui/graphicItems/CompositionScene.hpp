// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef COMPOSITIONSCENE_HPP
#define COMPOSITIONSCENE_HPP

#include <core/Point.hpp>

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

class CompositionScene : public QGraphicsScene
{
    Q_OBJECT
  public:
    explicit CompositionScene(QObject *parent = 0);

  signals:
    void removeFromModel(QGraphicsItem *item);
    void addInstance(Point position);

  public slots:

  protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent * event);

};

#endif // COMPOSITIONSCENE_HPP
