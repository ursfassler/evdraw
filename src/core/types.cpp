#include "types.hpp"



std::ostream &operator<<(std::ostream &stream, const ConnectorSide &connectorSide)
{
  switch (connectorSide) {
    case ConnectorSide::Right: {
      stream << "right";
      break;
    }
    case ConnectorSide::Left: {
      stream << "left";
      break;
    }
  }
  return stream;
}
