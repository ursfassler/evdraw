#include "convert.hpp"

static const qreal PuPerScene = 1000;

qreal puToScene(PaperUnit value)
{
  return value / PuPerScene;
}

PaperUnit sceneToPu(qreal value)
{
  return qRound(value * PuPerScene);
}


QPointF puToScene(const Point &value)
{
  return QPointF(puToScene(value.x), puToScene(value.y));
}

Point sceneToPu(const QPointF &value)
{
  return Point(sceneToPu(value.x()), sceneToPu(value.y()));
}
