#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include "Endpoint.hpp"
#include "Segment.hpp"
#include <vector>
#include <ostream>

class ConnectionFactory;

class Connection final
{
  public:
    enum class Mode {
      Build,
      BuildToEnd,
      Finished,
    };

    Connection(Mode mode);
    ~Connection();

    Mode getMode() const;
    void buildFinished();

    void addSegment();

    PortPoint &getStart();
    PortPoint &getEnd();

    const std::vector<HorizontalSegment *> &getHorizontalSegment() const;
    void addHorizontalSegment(HorizontalSegment *segment);

    const std::vector<VerticalSegment *> &getVerticalSegment() const;
    void addVerticalSegment(VerticalSegment *segment);

    const std::vector<IntermediatePoint *> &getIntermediatePoints() const;
    void addIntermediatePoint(IntermediatePoint *point);

  private:
    Mode        mode;

    PortPoint  start;
    PortPoint  end;
    std::vector<IntermediatePoint *> intermediatePoints;

    std::vector<HorizontalSegment *> horizontalSegments;
    std::vector<VerticalSegment *>   verticalSegments;

    void addHorizontalSegment();
    void addVerticalSegment();

    void initBuildToEnd();
    void finishBuildToEnd();

    void checkInvariants() const;

    friend ConnectionFactory;
};

std::ostream &operator<<(std::ostream &stream, Connection::Mode mode);

#endif // CONNECTION_HPP
