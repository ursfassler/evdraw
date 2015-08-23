// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef INSTANCEAPPEARANCE_HPP
#define INSTANCEAPPEARANCE_HPP

#include "Component.hpp"
#include "ComponentPort.hpp"
#include "../types.hpp"
#include "../Point.hpp"

class InstanceAppearanceTest;

class InstanceAppearance final
{
  public:
    static PaperUnit width();
    static PaperUnit height(const Component &component);
    static PaperUnit textHeight();
    static Point portDimension();
    static Point leftPortPosition(unsigned index);
    static Point rightPortPosition(unsigned index);
    static PaperUnit portVerticalOffset(unsigned index);
    static PaperUnit connectorOffset();
    static PaperUnit portWidth();
    static PaperUnit portHeight();

  private:
    static PaperUnit portOverlap();
    static PaperUnit topPortDistance();
    static PaperUnit verticalPortDistance();
    static PaperUnit verticalPortSpacing();
    static PaperUnit bottomPortDistance();
    static PaperUnit leftPortXOffset();
    static PaperUnit rightPortXOffset();

    static PaperUnit scale(int value);

    friend InstanceAppearanceTest;
};

#endif // INSTANCEAPPEARANCE_HPP
