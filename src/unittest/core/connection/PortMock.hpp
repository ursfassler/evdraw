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

    virtual void addConnectionPoint(RelativePosition *port) override;
    virtual void removeConnectionPoint(RelativePosition *port) override;
    virtual std::string getName() const override;
    RelativePosition &getPosition() override;
    void accept(Visitor &visitor) override;
    void accept(ConstVisitor &visitor) const override;

    std::set<RelativePosition*> ports{};
    std::string name{""};
    RelativePosition position{Point{0,0}};
};

#endif // PORTMOCK_H
