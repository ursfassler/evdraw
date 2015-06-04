#ifndef SIMPLEPORT_HPP
#define SIMPLEPORT_HPP

#include "AbstractPort.hpp"
#include "../base/Position.hpp"

#include <set>

class SimplePort : public AbstractPort
{
  public:
    virtual void addConnectionPoint(RelativePosition *port);
    virtual void removeConnectionPoint(RelativePosition *port);

    std::set<RelativePosition*> ports;

};


#endif // SIMPLEPORT_HPP
