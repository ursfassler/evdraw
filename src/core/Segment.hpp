#ifndef SEGMENT_HPP
#define SEGMENT_HPP

#include "Endpoint.hpp"

class Segment : private EndpointListener
{
  public:
    Segment(Endpoint *aStart, Endpoint *aEnd);
    virtual ~Segment();

    Endpoint *getStart() const;
    Endpoint *getEnd() const;

    bool moveable() const;

  private:
    Endpoint  * const start;
    Endpoint  * const end;

};

class HorizontalSegment : public Segment
{
  public:
    HorizontalSegment(Endpoint *aStart, Endpoint *aEnd);

    PaperUnit getY() const;
    void moveToY(PaperUnit value);

  private:
    void changeY(Endpoint *sender, PaperUnit value);
};

class VerticalSegment : public Segment
{
  public:
    VerticalSegment(Endpoint *aStart, Endpoint *aEnd);

    PaperUnit getX() const;
    void moveToX(PaperUnit value);

  private:
    void changeX(Endpoint *sender, PaperUnit value);
};

#endif // SEGMENT_HPP
