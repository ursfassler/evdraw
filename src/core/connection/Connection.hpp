#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include "Endpoint.hpp"
#include "Segment.hpp"
#include <vector>
#include <ostream>

class ConnectionFactory;
class ConnectionTest;

class ConnectionBase
{
  public:
    ConnectionBase();
    virtual ~ConnectionBase();

    PortPoint &getStart();
    PortPoint &getEnd();

    const std::vector<HorizontalSegment *> &getHorizontalSegment() const;
    const std::vector<VerticalSegment *> &getVerticalSegment() const;
    const std::vector<IntermediatePoint *> &getIntermediatePoints() const;

  protected:
    virtual void checkInvariants() const;
    void addIntermediatePoint(IntermediatePoint *point);
    void addHorizontalSegment(HorizontalSegment *segment);
    void addVerticalSegment(VerticalSegment *segment);

  private:
    PortPoint  start;
    PortPoint  end;
    std::vector<IntermediatePoint *> intermediatePoints;

    std::vector<HorizontalSegment *> horizontalSegments;
    std::vector<VerticalSegment *>   verticalSegments;

    friend ConnectionFactory;
    friend ConnectionTest;

};

class Connection final : public ConnectionBase
{
  protected:
    virtual void checkInvariants() const;

  private:
    friend ConnectionFactory;
};

class PartialConnectionFromStart final : public ConnectionBase
{
  public:
    void addSegment();
    void buildFinished();

  private:
    void insertHorizontalSegment();
    void insertVerticalSegment();

};

#endif // CONNECTION_HPP
