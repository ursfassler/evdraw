#include "ChildRemover.hpp"

#include "../implementation/Composition.hpp"
#include "../instance/InstanceFactory.hpp"

#include <set>

ChildRemover::ChildRemover(const Specification &aSpecification) :
  specification(aSpecification)
{
}

void ChildRemover::visit(Composition &composition)
{
  std::set<Instance*> removable;
  for (Instance *instance : composition.getInstances())
  {
    if (specification.isSatisfiedBy(instance))
    {
      removable.insert(instance);
    }
  }
  for (Instance *instance : removable)
  {
    composition.removeInstance(instance);
    InstanceFactory::dispose(instance);
  }
  DefaultVisitor::visit(composition);
}

