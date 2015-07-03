#include "CompositionScene.hpp"

#include <QDebug>

CompositionScene::CompositionScene(QObject *parent) :
  QGraphicsScene(parent)
{
}

void CompositionScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
  if (event->modifiers().testFlag(Qt::ControlModifier)) {
    QGraphicsItem * item = itemAt(event->scenePos(), QTransform());
    if (item) {
      removeFromModel(item);
    }
    event->accept();
  } else {
    QGraphicsScene::mousePressEvent(event);
  }
}
