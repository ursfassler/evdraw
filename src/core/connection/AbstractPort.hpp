#ifndef ABSTRACTPORT_HPP
#define ABSTRACTPORT_HPP

#include "../base/Position.hpp"
#include "../visitor/VisitorClient.hpp"

class AbstractPort : public VisitorClient
{
  public:
    virtual ~AbstractPort(){}
    virtual void addConnectionPoint(RelativePosition *point) = 0;
    virtual void removeConnectionPoint(RelativePosition *point) = 0;
    virtual std::string getName() const = 0;
    virtual Point getPosition() const = 0;
};


#endif // ABSTRACTPORT_HPP
