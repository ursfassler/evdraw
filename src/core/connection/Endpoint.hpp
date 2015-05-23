#ifndef ENDPOINT_HPP
#define ENDPOINT_HPP

#include <list>
#include <ostream>

#include "../util/Observed.hpp"
#include "../types.hpp"

class Endpoint;

class EndpointListener
{
  public:
    virtual ~EndpointListener();
    virtual void changeX(const Endpoint *sender);
    virtual void changeY(const Endpoint *sender);

};

class Endpoint
{
  public:
    Endpoint(PaperUnit aX, PaperUnit aY);
    virtual ~Endpoint();

    PaperUnit getX() const;
    void setX(PaperUnit value);

    PaperUnit getY() const;
    void setY(PaperUnit value);

    virtual bool freeMovable() const = 0;

    bool operator==(const Endpoint &other) const
    {
      return (x == other.x) && (y == other.y);
    }

    Observed<Endpoint, EndpointListener> listener;

  private:

    PaperUnit   x;
    PaperUnit   y;
};

std::ostream &operator<<(std::ostream &stream, const Endpoint &endpoint);

class PortPoint : public Endpoint
{
  public:
    PortPoint(PaperUnit aX, PaperUnit aY);
    bool freeMovable() const;

};

class IntermediatePoint : public Endpoint
{
  public:
    IntermediatePoint(PaperUnit aX, PaperUnit aY);
    bool freeMovable() const;

};


#endif
