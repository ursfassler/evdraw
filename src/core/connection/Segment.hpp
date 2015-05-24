#ifndef SEGMENT_HPP
#define SEGMENT_HPP

#include "../util/Observer.hpp"
#include "Endpoint.hpp"

class Segment : protected Observer<Endpoint>, public ObserverCollection<Segment>
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

    void notify(const Endpoint *subject);
};

class HorizontalSegment : public Segment
{
  public:
    HorizontalSegment(Endpoint *aStart, Endpoint *aEnd);

    PaperUnit getY() const;
    void moveToY(PaperUnit value);

  private:
    void notify(const Endpoint *sender);
};

class VerticalSegment : public Segment
{
  public:
    VerticalSegment(Endpoint *aStart, Endpoint *aEnd);

    PaperUnit getX() const;
    void moveToX(PaperUnit value);

  private:
    void notify(const Endpoint *sender);
};

#endif // SEGMENT_HPP
