// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef COMPOSITIONDRAW_HPP
#define COMPOSITIONDRAW_HPP

#include "CompositionToGuiUpdater.hpp"
#include "graphicItems/CompositionScene.hpp"
#include "graphicItems/GiSelfInstance.hpp"

#include <core/implementation/Composition.hpp>

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsSimpleTextItem>

class CompositionDraw :
    public QGraphicsView
{
    Q_OBJECT
  public:
    explicit CompositionDraw(Composition &composition, QWidget *parent = 0);

  signals:
    void addInstance(Point position, Composition &composition);

  public slots:

  private slots:
    void removeFromModel(QGraphicsItem *item);
    void addInstance(Point position);

  private:
    CompositionScene scene;
    GiSelfInstance selfInst;
    CompositionToGuiUpdater updater;
    Composition &composition;

};

#endif
