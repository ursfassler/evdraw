#ifndef SEGMENT_HPP
#define SEGMENT_HPP

#include "Endpoint.hpp"

class Segment : private EndpointListener
{
  public:
    Segment(Endpoint &aStart, Endpoint &aEnd);
    virtual ~Segment();

    const Endpoint &getStart() const;
    const Endpoint &getEnd() const;

    bool moveable() const;

  protected:
    Endpoint  &start;
    Endpoint  &end;

};

class HorizontalSegment : public Segment
{
  public:
    HorizontalSegment(Endpoint &aStart, Endpoint &aEnd);

    PaperUnit getY() const;
    void moveToY(PaperUnit value);

  private:
    void changeY(Endpoint *sender, PaperUnit value);
};

class VerticalSegment : public Segment
{
  public:
    VerticalSegment(Endpoint &aStart, Endpoint &aEnd);

    PaperUnit getX() const;
    void moveToX(PaperUnit value);

  private:
    void changeX(Endpoint *sender, PaperUnit value);
};

#endif // SEGMENT_HPP
