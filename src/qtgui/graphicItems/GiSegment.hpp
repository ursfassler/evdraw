#ifndef GISEGMENT_HPP
#define GISEGMENT_HPP

#include <core/Segment.hpp>

#include <QGraphicsLineItem>
#include <QGraphicsSceneMouseEvent>


class GiSegment : public QGraphicsLineItem, public SegmentListener
{
  public:
    explicit GiSegment(Segment *model, QGraphicsItem *parent);
    virtual ~GiSegment();

  protected:
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent * event);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent * event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent * event);
    virtual void positionChange(const Segment *sender);
    virtual Segment *getModel() = 0;

  private:
    void updatePosition(Segment *model);
};

class GiUnmoveableSegment : public GiSegment
{
  public:
    GiUnmoveableSegment(Segment *aModel, QGraphicsItem *parent);

  protected:
    Segment *getModel();

  private:
    Segment * const model;
};

class GiHorizontalSegment : public GiSegment
{
  public:
    GiHorizontalSegment(HorizontalSegment *aModel, QGraphicsItem *parent);

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

  protected:
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent * event);
    Segment *getModel();

  private:
    VerticalSegment * const model;
};

#endif // GISEGMENT_HPP
