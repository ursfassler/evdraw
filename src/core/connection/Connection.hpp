#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include "Endpoint.hpp"
#include "Segment.hpp"
#include "../util/Observer.hpp"
#include <vector>
#include <ostream>

class ConnectionFactory;
class ConnectionTest;

class ConnectionBase;

class ConnectionObserver
{
  public:
    virtual ~ConnectionObserver()
    {
    }

    virtual void addVerticalSegment(const ConnectionBase *parent, VerticalSegment *segment)
    {
      (void)(parent);
      (void)(segment);
    }

    virtual void addHorizontalSegment(const ConnectionBase *parent, HorizontalSegment *segment)
    {
      (void)(parent);
      (void)(segment);
    }
};

class ConnectionBase : public ObserverCollection<ConnectionObserver>
{
  public:
    ConnectionBase();
    virtual ~ConnectionBase();

    const std::vector<HorizontalSegment *> &getHorizontalSegment() const;
    const std::vector<VerticalSegment *> &getVerticalSegment() const;
    const std::vector<Endpoint *> &getPoints() const;

  protected:
    virtual void checkInvariants() const;
    void addPoint(Endpoint *point);
    void addHorizontalSegment(HorizontalSegment *segment);
    void addVerticalSegment(VerticalSegment *segment);

    std::vector<Endpoint *> points;
    std::vector<HorizontalSegment *> horizontalSegments;
    std::vector<VerticalSegment *>   verticalSegments;

    friend ConnectionFactory;
    friend ConnectionTest;

};

class Connection final : public ConnectionBase
{
  public:
    Endpoint *getStart();
    Endpoint *getEnd();

  protected:
    virtual void checkInvariants() const;

  private:
    friend ConnectionFactory;
};

class ConstructionConnection final : public ConnectionBase
{
  public:
    Endpoint *getRoot();
    Endpoint *getLeaf();
    const Endpoint *getRoot() const;
    const Endpoint *getLeaf() const;

    void addSegment();

  protected:
    virtual void checkInvariants() const;

  private:
    void insertHorizontalSegment();
    void insertVerticalSegment();

    friend ConnectionFactory;
};

#endif // CONNECTION_HPP
