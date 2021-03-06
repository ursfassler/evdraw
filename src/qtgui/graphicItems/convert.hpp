// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef CONVERT_HPP
#define CONVERT_HPP

#include <core/types.hpp>
#include <core/Point.hpp>
#include <QPointF>

qreal puToScene(PaperUnit value);
PaperUnit sceneToPu(qreal value);

QPointF puToScene(const Point &value);
Point sceneToPu(const QPointF &value);

#endif // CONVERT_HPP
