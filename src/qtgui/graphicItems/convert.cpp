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
