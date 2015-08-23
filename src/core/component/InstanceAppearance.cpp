// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "InstanceAppearance.hpp"

#include "../util/list.hpp"

PaperUnit InstanceAppearance::textHeight()
{
  return scale(20);
}

PaperUnit InstanceAppearance::width()
{
  return scale(160);
}

PaperUnit InstanceAppearance::height(const Component &component)
{
   const size_t count = component.height();
   return (count-1) * verticalPortDistance() + topPortDistance() + bottomPortDistance();
}

PaperUnit InstanceAppearance::portWidth()
{
  return scale(90);
}

PaperUnit InstanceAppearance::portHeight()
{
  return scale(20);
}

PaperUnit InstanceAppearance::topPortDistance()
{
  return scale(60);
}

PaperUnit InstanceAppearance::verticalPortDistance()
{
  return portHeight() + verticalPortSpacing();
}

PaperUnit InstanceAppearance::verticalPortSpacing()
{
  return scale(10);
}

PaperUnit InstanceAppearance::portOverlap()
{
  return scale(20);
}

PaperUnit InstanceAppearance::bottomPortDistance()
{
  return verticalPortDistance();
}

Point InstanceAppearance::portDimension()
{
  return Point(portWidth(), portHeight());
}

Point InstanceAppearance::leftPortPosition(unsigned index)
{
  return Point(leftPortXOffset(), portVerticalOffset(index));
}

Point InstanceAppearance::rightPortPosition(unsigned index)
{
  return Point(rightPortXOffset(), portVerticalOffset(index));
}

PaperUnit InstanceAppearance::connectorOffset()
{
  return rightPortXOffset() + portWidth()/2;
}

PaperUnit InstanceAppearance::leftPortXOffset()
{
  return -rightPortXOffset();
}

PaperUnit InstanceAppearance::rightPortXOffset()
{
  return portOverlap() + (width() - portWidth()) / 2;
}

PaperUnit InstanceAppearance::portVerticalOffset(unsigned index)
{
  return index * verticalPortDistance() + topPortDistance();
}

PaperUnit InstanceAppearance::scale(int value)
{
  return value * 1000;
}


