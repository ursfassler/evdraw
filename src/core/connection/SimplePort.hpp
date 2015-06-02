#ifndef SIMPLEPORT_HPP
#define SIMPLEPORT_HPP

#include "AbstractPort.hpp"
#include "../base/Base.hpp"

#include <set>

class SimplePort : public AbstractPort
{
  public:
    virtual void addConnectionPoint(Positionable *port);
    virtual void removeConnectionPoint(Positionable *port);

    std::set<Positionable*> ports;

};


#endif // SIMPLEPORT_HPP
