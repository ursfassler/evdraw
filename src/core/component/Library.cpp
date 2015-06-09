#include "Library.hpp"

#include "../util/list.hpp"

#include <stdexcept>

Library::~Library()
{
  for (Component *component : components) {
    delete component;
  }
  components.clear();
}

void Library::add(Component *component)
{
  components.push_back(component);
}

bool Library::contains(const Component *component) const
{
  return ::contains(components.begin(), components.end(), component);
}

const std::list<Component *> Library::getComponents() const
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
