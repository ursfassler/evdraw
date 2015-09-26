// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef INSTANCEAPPEARANCE_HPP
#define INSTANCEAPPEARANCE_HPP

#include "../types.hpp"
#include "../Point.hpp"

class InstanceAppearanceTest;

class InstanceAppearance final
{
  public:
    static PaperUnit componentWidth();
    static PaperUnit textHeight();
    static Point portDimension();
    static PaperUnit portVerticalOffset(unsigned index);
    static PaperUnit connectorOffset();
    static PaperUnit portWidth();
    static PaperUnit portHeight();
    static PaperUnit topPortDistance();
    static PaperUnit verticalPortDistance();
    static PaperUnit bottomPortDistance();
    static PaperUnit portOverlap();

  private:
    static PaperUnit verticalPortSpacing();
    static PaperUnit leftPortXOffset();
    static PaperUnit rightPortXOffset();

    static PaperUnit scale(int value);

    friend InstanceAppearanceTest;
};

#endif // INSTANCEAPPEARANCE_HPP
