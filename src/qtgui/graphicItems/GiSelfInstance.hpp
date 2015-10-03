// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef GISELFINSTANCE_H
#define GISELFINSTANCE_H

#include "MoveableLine.hpp"

#include <core/implementation/Composition.hpp>

#include <QGraphicsSimpleTextItem>

class VerticalLine :
    public MoveableLine
{
  public:
    VerticalLine(ICompositionInstance &instance, QGraphicsItem *parent);

  protected:
    void moveTo(const Point &pos) override;

  private:
    ICompositionInstance &instance;

};

class HorizontallLine :
    public MoveableLine
{
  public:
    HorizontallLine(ICompositionInstance &instance, QGraphicsItem *parent);

  protected:
    void moveTo(const Point &pos) override;

  private:
    ICompositionInstance &instance;

};

class GiSelfInstance :
    public QGraphicsRectItem,
    private InstanceObserver
{
  public:
    GiSelfInstance(ICompositionInstance &instance, Composition &aComposition);
    ~GiSelfInstance();

  signals:
    void dimensionChanged();

  private:
    QGraphicsSimpleTextItem type;
    VerticalLine leftLine;
    VerticalLine rightLine;
    HorizontallLine bottomLine;
    ICompositionInstance &instance;
    Composition &composition;

    void addPorts(const std::vector<InstancePort *> &ports);
    void addPort(InstancePort *port);

    void widthChanged() override;
    void heightChanged() override;

    void updateSize();
};

#endif // GISELFINSTANCE_H
