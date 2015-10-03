// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef GISEGMENT_HPP
#define GISEGMENT_HPP

#include <core/connection/Segment.hpp>

#include <QGraphicsLineItem>
#include <QGraphicsSceneMouseEvent>


class GiSegment :
    public QGraphicsLineItem,
    public SegmentObserver
{
  public:
    explicit GiSegment(Segment *model, QGraphicsItem *parent);
    virtual ~GiSegment();

  protected:
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent * event);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent * event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent * event);
    virtual void positionChanged(const Segment *sender);
    virtual Segment *getModel() = 0;

  private:
    void updatePosition(Segment *model);
};

class GiHorizontalSegment : public GiSegment
{
  public:
    GiHorizontalSegment(HorizontalSegment *aModel, QGraphicsItem *parent);
    virtual ~GiHorizontalSegment();

  protected:
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent * event);
    Segment *getModel();

  private:
    HorizontalSegment * const model;
};

class GiVerticalSegment : public GiSegment
{
  public:
    GiVerticalSegment(VerticalSegment *aModel, QGraphicsItem *parent);
    virtual ~GiVerticalSegment();

  protected:
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent * event);
    Segment *getModel();

  private:
    VerticalSegment * const model;
};

#endif // GISEGMENT_HPP
