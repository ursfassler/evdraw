// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef POINT_HPP
#define POINT_HPP

#include "types.hpp"
#include <ostream>

class Point final
{
  public:
    Point(PaperUnit aX, PaperUnit aY);

    PaperUnit x;
    PaperUnit y;
};

bool operator==(const Point &left, const Point &right);
bool operator!=(const Point &left, const Point &right);
Point operator+(const Point &left, const Point &right);
Point operator-(const Point &left, const Point &right);
Point operator-(const Point &point);
Point operator/(const Point &point, PaperUnit divisor);
std::ostream &operator<<(std::ostream &stream, const Point &point);


#endif // POINT_HPP
