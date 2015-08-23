// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef COMPOSITIONEDITOR_HPP
#define COMPOSITIONEDITOR_HPP

#include "CompositionToGuiUpdater.hpp"
#include "graphicItems/CompositionScene.hpp"

#include <core/implementation/Composition.hpp>

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>

class CompositionEditor : public QGraphicsView
{
    Q_OBJECT
  public:
    explicit CompositionEditor(Composition &composition, QWidget *parent = 0);

  signals:
    void addInstance(Point position, Composition &composition);

  public slots:

  private slots:
    void removeFromModel(QGraphicsItem *item);
    void addInstance(Point position);

  private:
    CompositionScene scene;
    CompositionToGuiUpdater updater;
    Composition &composition;

};

#endif // COMPOSITIONEDITOR_HPP
