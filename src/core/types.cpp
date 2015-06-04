#include "types.hpp"



std::ostream &operator<<(std::ostream &stream, const Side &connectorSide)
{
  switch (connectorSide) {
    case Side::Right: {
      stream << "right";
      break;
    }
    case Side::Left: {
      stream << "left";
      break;
    }
  }
  return stream;
}
