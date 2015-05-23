#ifndef TYPES_HPP
#define TYPES_HPP

#include <cstdint>
#include <ostream>

typedef std::int32_t PaperUnit;

class Point final
{
  public:
    Point(PaperUnit aX, PaperUnit aY);

    const PaperUnit x;
    const PaperUnit y;
};

std::ostream &operator<<(std::ostream &stream, const Point &point);

enum class ConnectorSide
{
    Right,
    Left
};

std::ostream &operator<<(std::ostream &stream, const ConnectorSide &connectorSide);

#endif
