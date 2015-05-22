#ifndef SEGMENT_HPP
#define SEGMENT_HPP

#include "Endpoint.hpp"

class Segment;

class SegmentListener
{
  public:
    virtual ~SegmentListener();
    virtual void positionChange(Segment *sender);
};

class Segment : protected EndpointListener
{
  public:
    Segment(Endpoint *aStart, Endpoint *aEnd);
    Segment(const Segment &copy) = delete;
    virtual ~Segment();
    Segment & operator=(const Segment &L) = delete;

    Endpoint *getStart() const;
    Endpoint *getEnd() const;

    bool moveable() const;

    bool hasListener() const;
    void addListener(SegmentListener *listener);
    void removeListener(SegmentListener *listener);

  protected:
    Endpoint  * const start;
    Endpoint  * const end;

    void changeX(Endpoint *sender);
    void changeY(Endpoint *sender);

  private:
    std::list<SegmentListener*> listeners;
    void notifyPositionChange();

};

class HorizontalSegment : public Segment
{
  public:
    HorizontalSegment(Endpoint *aStart, Endpoint *aEnd);

    PaperUnit getY() const;
    void moveToY(PaperUnit value);

  private:
    void changeY(Endpoint *sender);
};

class VerticalSegment : public Segment
{
  public:
    VerticalSegment(Endpoint *aStart, Endpoint *aEnd);

    PaperUnit getX() const;
    void moveToX(PaperUnit value);

  private:
    void changeX(Endpoint *sender);
};

#endif // SEGMENT_HPP
