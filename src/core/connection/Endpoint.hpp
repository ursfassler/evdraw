#ifndef ENDPOINT_HPP
#define ENDPOINT_HPP

#include <list>
#include <ostream>

#include "../util/Observer.hpp"
#include "../Point.hpp"
#include "../base/Position.hpp"

class Endpoint final : public RelativePosition
{
  public:
    Endpoint(const Point &position);

    bool freeMovable() const;
};

std::ostream &operator<<(std::ostream &stream, const Endpoint &endpoint);


#endif
