#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include "Endpoint.hpp"
#include "Segment.hpp"
#include "AbstractPort.hpp"
#include "../util/Observer.hpp"
#include <vector>
#include <ostream>

class ConnectionFactory;
class ConnectionTest;

class Connection;

class ConnectionObserver
{
  public:
    virtual ~ConnectionObserver()
    {
    }

    virtual void addVerticalSegment(const Connection *parent, VerticalSegment *segment)
    {
      (void)(parent);
      (void)(segment);
    }

    virtual void addHorizontalSegment(const Connection *parent, HorizontalSegment *segment)
    {
      (void)(parent);
      (void)(segment);
    }
};

class Connection : public ObserverCollection<ConnectionObserver>
{
  public:
    Connection(AbstractPort *startPort, AbstractPort *endPort);
    virtual ~Connection();

    AbstractPort *getStartPort() const;
    void replaceStartPort(AbstractPort *port);
    AbstractPort *getEndPort() const;
    void replaceEndPort(AbstractPort *port);

    const std::vector<HorizontalSegment *> &getHorizontalSegment() const;
    const std::vector<VerticalSegment *> &getVerticalSegment() const;
    const std::vector<Endpoint *> &getPoints() const;

    void insertSegmentAtEnd();

  protected:
    virtual void checkInvariants() const;
    void addPoint(Endpoint *point);
    void addHorizontalSegment(HorizontalSegment *segment);
    void addVerticalSegment(VerticalSegment *segment);

    std::vector<Endpoint *> points;
    std::vector<HorizontalSegment *> horizontalSegments;
    std::vector<VerticalSegment *>   verticalSegments;

  private:
    AbstractPort *startPort;
    AbstractPort *endPort;
    void insertHorizontalSegment();
    void insertVerticalSegment();
    Segment *getSegment(size_t index) const;

    friend ConnectionFactory;
    friend ConnectionTest;
};

#endif // CONNECTION_HPP
