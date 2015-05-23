#include "InstanceAppearance.hpp"

#include <stdexcept>

InstanceAppearance::InstanceAppearance(const Component *aComponent) :
  component(aComponent)
{
}

PaperUnit InstanceAppearance::width() const
{
  return scale(100);
}

PaperUnit InstanceAppearance::height() const
{
   size_t count = std::max(component->getPortLeft().size(), component->getPortRight().size());
   return scale(count * 15 + 35);
}

PaperUnit InstanceAppearance::portWidth() const
{
  return scale(45);
}

PaperUnit InstanceAppearance::portHeight() const
{
  return scale(10);
}

PaperUnit InstanceAppearance::leftPortXOffset() const
{
  return (-width() + portWidth()) / 2;
}

PaperUnit InstanceAppearance::leftPortYOffset(const ComponentPort *port) const
{
  unsigned index = indexOf(port, component->getPortLeft());
  return portOffset(index);
}

PaperUnit InstanceAppearance::rightPortXOffset() const
{
  return (width() - portWidth()) / 2;
}

PaperUnit InstanceAppearance::rightPortYOffset(const ComponentPort *port) const
{
  unsigned index = indexOf(port, component->getPortRight());
  return portOffset(index);
}

PaperUnit InstanceAppearance::scale(int value) const
{
  return value * 1000;
}

unsigned InstanceAppearance::indexOf(const ComponentPort *port, const std::vector<ComponentPort *> &list) const
{
  for (unsigned i = 0; i < list.size(); i++) {
    if (list[i] == port) {
      return i;
    }
  }

  throw std::invalid_argument("element not in list");
}

PaperUnit InstanceAppearance::portOffset(unsigned index) const
{
  return scale(index * 15 + 25);
}
