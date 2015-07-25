#include "Library.hpp"

#include "ComponentFactory.hpp"
#include "../util/list.hpp"
#include "../instance/InstanceOfSpecification.hpp"
#include "../util/ChildRemover.hpp"

#include <stdexcept>

Library::Library() :
  components()
{
}

Library::~Library()
{
  while (!components.empty()) {
    del(components.back());
  }
  postcondition(components.empty());
}

void Library::add(Component *component)
{
  components.push_back(component);
  notify(&LibraryObserver::addComponent, static_cast<const Library*>(this), component);
}

void Library::del(Component *component)
{
  std::vector<Component*>::iterator idx = std::find(components.begin(), components.end(), component);
  precondition(idx != components.end());

  InstanceOfSpecification spec(component);
  ChildRemover remover(spec);
  this->accept(remover);

  components.erase(idx);
  notify(&LibraryObserver::delComponent, static_cast<const Library*>(this), component);
  ComponentFactory::dispose(component);
}

bool Library::contains(const Component *component) const
{
  return ::contains(components.begin(), components.end(), component);
}

const std::vector<Component *> Library::getComponents() const
{
  return components;
}

Component *Library::getComponent(const std::string &name) const
{
  auto predicate = [&](Component *itr){
    return itr->getName() == name;
  };
  return listGet<Component*>(components.begin(), components.end(), predicate);
}

void Library::accept(Visitor &visitor)
{
  visitor.visit(*this);
}

void Library::accept(ConstVisitor &visitor) const
{
  visitor.visit(*this);
}
