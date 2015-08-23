// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

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
