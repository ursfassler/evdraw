#ifndef COMPOSITIONSCENE_HPP
#define COMPOSITIONSCENE_HPP

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

class CompositionScene : public QGraphicsScene
{
    Q_OBJECT
  public:
    explicit CompositionScene(QObject *parent = 0);

  signals:
    void removeFromModel(QGraphicsItem *item);

  public slots:

  protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent * event);

};

#endif // COMPOSITIONSCENE_HPP
