#ifndef SEGMENT_HPP
#define SEGMENT_HPP

#include "../util/Observed.hpp"
#include "Endpoint.hpp"

class Segment;

class SegmentListener
{
  public:
    virtual ~SegmentListener();
    virtual void positionChange(const Segment *sender);
};

class Segment : protected EndpointListener, public Observed<Segment, SegmentListener>
{
  public:
    Segment(Endpoint *aStart, Endpoint *aEnd);
    Segment(const Segment &copy) = delete;
    virtual ~Segment();
    Segment & operator=(const Segment &L) = delete;

    Endpoint *getStart() const;
    Endpoint *getEnd() const;

    bool moveable() const;

  protected:
    Endpoint  * const start;
    Endpoint  * const end;

    void changeX(const Endpoint *sender);
    void changeY(const Endpoint *sender);
};

class HorizontalSegment : public Segment
{
  public:
    HorizontalSegment(Endpoint *aStart, Endpoint *aEnd);

    PaperUnit getY() const;
    void moveToY(PaperUnit value);

  private:
    void changeY(const Endpoint *sender);
};

class VerticalSegment : public Segment
{
  public:
    VerticalSegment(Endpoint *aStart, Endpoint *aEnd);

    PaperUnit getX() const;
    void moveToX(PaperUnit value);

  private:
    void changeX(const Endpoint *sender);
};

#endif // SEGMENT_HPP
