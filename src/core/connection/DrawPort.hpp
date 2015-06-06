#ifndef DRAWPORT_HPP
#define DRAWPORT_HPP

#include "AbstractPort.hpp"
#include "../base/Position.hpp"

class DrawPort : public AbstractPort, public RelativePosition
{
  public:
    DrawPort(const Point &offset);
    void addConnectionPoint(RelativePosition *point);
    void removeConnectionPoint(RelativePosition *point);
    void accept(Visitor &visitor) const;
};

#endif // DRAWPORT_HPP
