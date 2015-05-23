#include "InstanceAppearance.hpp"


InstanceAppearance::InstanceAppearance(const Component *aComponent) :
  component(aComponent)
{
}

PaperUnit InstanceAppearance::width() const
{
  return 100 * 1000;
}

PaperUnit InstanceAppearance::height() const
{
   size_t count = std::max(component->getPortLeft().size(), component->getPortRight().size());
   return count * 15 + 35;
}
