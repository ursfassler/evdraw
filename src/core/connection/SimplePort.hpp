#ifndef SIMPLEPORT_HPP
#define SIMPLEPORT_HPP

#include "AbstractPort.hpp"
#include "../base/Position.hpp"

#include <set>

class SimplePort : public AbstractPort
{
  public:
    SimplePort();
    SimplePort(const Point &position);

    virtual void addConnectionPoint(RelativePosition *port);
    virtual void removeConnectionPoint(RelativePosition *port);
    virtual std::string getName() const;
    Point getPosition() const;
    void accept(Visitor &visitor);
    void accept(ConstVisitor &visitor) const;

    std::set<RelativePosition*> ports;

  private:
    const Point position;
};


#endif // SIMPLEPORT_HPP
