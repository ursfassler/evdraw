#ifndef ENDPOINT_HPP
#define ENDPOINT_HPP

#include <list>
#include <ostream>

#include "../util/Observer.hpp"
#include "../types.hpp"

class Endpoint : public ObserverCollection<Endpoint>
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
