// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include "Endpoint.hpp"
#include "Segment.hpp"
#include "IPort.hpp"
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
    Connection(IPort *startPort, IPort *endPort);
    virtual ~Connection();

    Connection(const Connection &) = delete;
    Connection operator=(const Connection &) = delete;

    IPort *getStartPort() const;
    void replaceStartPort(IPort *port);
    IPort *getEndPort() const;
    void replaceEndPort(IPort *port);

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

    std::vector<Endpoint *> points;   //TODO replace with List
    std::vector<HorizontalSegment *> horizontalSegments; //TODO replace with List
    std::vector<VerticalSegment *>   verticalSegments;   //TODO replace with List

  private:
    IPort *startPort;
    IPort *endPort;
    void insertHorizontalSegment();
    void insertVerticalSegment();
    Segment *getSegment(size_t index) const;

    friend ConnectionFactory;
    friend ConnectionTest;
};

#endif // CONNECTION_HPP
