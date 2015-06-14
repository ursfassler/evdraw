#ifndef COMPOSITIONEDITOR_HPP
#define COMPOSITIONEDITOR_HPP

#include "CompositionToGuiUpdater.hpp"

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

  public slots:

  private:
    QGraphicsScene scene;
    CompositionToGuiUpdater updater;
    Composition &composition;

};

#endif // COMPOSITIONEDITOR_HPP
