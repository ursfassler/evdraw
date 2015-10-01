// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef GISELFINSTANCE_H
#define GISELFINSTANCE_H

#include <core/implementation/Composition.hpp>

#include <QGraphicsSimpleTextItem>

class GiSelfInstance :
    public QGraphicsRectItem
{
  public:
    GiSelfInstance(ICompositionInstance &instance, Composition &aComposition);

  private:
    QGraphicsSimpleTextItem type;
    Composition &composition;

    void addPorts(const std::vector<InstancePort *> &ports);
    void addPort(InstancePort *port);

};

#endif // GISELFINSTANCE_H
