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

    const std::vector<HorizontalSegment *> &getHorizontalSegment() const;
    void addHorizontalSegment(HorizontalSegment *segment);

    const std::vector<VerticalSegment *> &getVerticalSegment() const;
    void addVerticalSegment(VerticalSegment *segment);

    const std::vector<IntermediatePoint *> &getIntermediatePoints() const;
    void addIntermediatePoint(IntermediatePoint *point);

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
