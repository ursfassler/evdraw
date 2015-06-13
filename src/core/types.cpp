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


std::ostream &operator<<(std::ostream &stream, const std::vector<PaperUnit> &path)
{
  stream << "[";

  bool first = true;
  for (PaperUnit itr : path) {
    if (first) {
      first = false;
    } else {
      stream << " ";
    }
    stream << itr;
  }

  stream << "]";

  return stream;
}
