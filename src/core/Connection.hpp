#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include "Endpoint.hpp"
#include "Segment.hpp"
#include <vector>

class ConnectionFactory;

class Connection final
{
  public:
    Connection();
    ~Connection();

    PortPoint &getStart();
    PortPoint &getEnd();

    const std::vector<HorizontalSegment *> getHorizontalSegment() const;
    const std::vector<VerticalSegment *> getVerticalSegment() const;
    const std::vector<IntermediatePoint *> &getIntermediatePoints() const;

  private:
    PortPoint  start;
    PortPoint  end;
    std::vector<IntermediatePoint *> intermediatePoints;

    std::vector<HorizontalSegment *> horizontalSegments;
    std::vector<VerticalSegment *>   verticalSegments;

    void checkInvariants() const;

    friend ConnectionFactory;
};

#endif // CONNECTION_HPP
