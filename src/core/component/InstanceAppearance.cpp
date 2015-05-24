#include "InstanceAppearance.hpp"

#include "../util/list.hpp"

PaperUnit InstanceAppearance::width()
{
  return scale(100);
}

PaperUnit InstanceAppearance::height(const Component &component)
{
   size_t count = std::max(component.getPortLeft().size(), component.getPortRight().size());
   return scale(count * 15 + 35);
}

PaperUnit InstanceAppearance::portWidth()
{
  return scale(45);
}

PaperUnit InstanceAppearance::portHeight()
{
  return scale(10);
}

PaperUnit InstanceAppearance::leftPortXOffset()
{
  return (-width() + portWidth()) / 2;
}

PaperUnit InstanceAppearance::rightPortXOffset()
{
  return (width() - portWidth()) / 2;
}

PaperUnit InstanceAppearance::scale(int value)
{
  return value * 1000;
}

PaperUnit InstanceAppearance::portYOffset(unsigned index)
{
  return scale(index * 15 + 25);
}
