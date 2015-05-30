#ifndef ENDPOINT_HPP
#define ENDPOINT_HPP

#include <list>
#include <ostream>

#include "../util/Observer.hpp"
#include "../Point.hpp"

class Endpoint;

class EndpointObserver
{
  public:
    virtual ~EndpointObserver(){}
    virtual void positionChanged(const Endpoint *sender) = 0;
};

class Endpoint : public ObserverCollection<EndpointObserver>
{
  public:
    Endpoint(const Point &position);
    virtual ~Endpoint();

    const Point &getPosition() const;
    void setPosition(const Point &value);

    virtual bool freeMovable() const = 0;

    bool operator==(const Endpoint &other) const
    {
      return position == other.position;
    }

  private:
    Point position;
};

std::ostream &operator<<(std::ostream &stream, const Endpoint &endpoint);

class PortPoint : public Endpoint
{
  public:
    PortPoint(const Point &position);
    bool freeMovable() const;

};

class IntermediatePoint : public Endpoint
{
  public:
    IntermediatePoint(const Point &position);
    bool freeMovable() const;

};


#endif
