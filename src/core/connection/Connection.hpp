#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include "Endpoint.hpp"
#include "Segment.hpp"
#include "AbstractPort.hpp"
#include "../util/Observer.hpp"
#include "../visitor/VisitorClient.hpp"
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

    virtual void verticalSegmentAdded(VerticalSegment *segment)
    {
      (void)(segment);
    }

    virtual void horizontalSegmentAdded(HorizontalSegment *segment)
    {
      (void)(segment);
    }
};

class Connection final : public ObserverCollection<ConnectionObserver>, public VisitorClient
{
  public:
    Connection(AbstractPort *startPort, AbstractPort *endPort);
    virtual ~Connection();

    Connection(const Connection &) = delete;
    Connection operator=(const Connection &) = delete;

    AbstractPort *getStartPort() const;
    void replaceStartPort(AbstractPort *port);
    AbstractPort *getEndPort() const;
    void replaceEndPort(AbstractPort *port);

    const std::vector<HorizontalSegment *> &getHorizontalSegment() const;
    const std::vector<VerticalSegment *> &getVerticalSegment() const;
    const std::vector<Endpoint *> &getPoints() const;
    std::vector<PaperUnit> getPath() const;

    void insertSegmentAtEnd();

    void accept(Visitor &visitor);
    void accept(ConstVisitor &visitor) const;

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
