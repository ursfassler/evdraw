#ifndef ABSTRACTPORT_HPP
#define ABSTRACTPORT_HPP

#include "../base/Position.hpp"

class AbstractPort
{
  public:
    virtual ~AbstractPort(){}
    virtual void addConnectionPoint(RelativePosition *point) = 0;
    virtual void removeConnectionPoint(RelativePosition *point) = 0;
};


#endif // ABSTRACTPORT_HPP
