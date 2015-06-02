#ifndef ABSTRACTPORT_HPP
#define ABSTRACTPORT_HPP

#include "../base/Base.hpp"

class AbstractPort
{
  public:
    virtual ~AbstractPort(){}
    virtual void addConnectionPoint(Positionable *point) = 0;
    virtual void removeConnectionPoint(Positionable *point) = 0;
};


#endif // ABSTRACTPORT_HPP
