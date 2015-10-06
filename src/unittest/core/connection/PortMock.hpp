#ifndef PORTMOCK_H
#define PORTMOCK_H

#include <core/connection/IPort.hpp>
#include <core/base/Position.hpp>

#include <string>
#include <set>

class PortMock :
    public IPort
{
  public:
    PortMock();
    PortMock(const Point &position);
    PortMock(const std::string &name);

    virtual void addConnectionPoint(RelativePosition *port);
    virtual void removeConnectionPoint(RelativePosition *port);
    virtual std::string getName() const;
    Point getPosition() const;
    void accept(Visitor &visitor);
    void accept(ConstVisitor &visitor) const;

    std::set<RelativePosition*> ports{};
    std::string name{""};
    Point position{0,0};
};

#endif // PORTMOCK_H
