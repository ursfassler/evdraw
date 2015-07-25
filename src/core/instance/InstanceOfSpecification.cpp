#include "InstanceOfSpecification.hpp"

#include "Instance.hpp"

InstanceOfSpecification::InstanceOfSpecification(const Component *aComponent) :
  component(aComponent)
{
}

InstanceOfSpecification::InstanceOfSpecification(const InstanceOfSpecification &copy) :
  component(copy.component)
{
}

InstanceOfSpecification &InstanceOfSpecification::operator=(const InstanceOfSpecification &right)
{
  component = right.component;
  return *this;
}

bool InstanceOfSpecification::isSatisfiedBy(const Base *candidate) const
{
  const Instance *instance = dynamic_cast<const Instance*>(candidate);
  if (instance == nullptr)
  {
    return false;
  }
  return instance->getComponent() == component;
}