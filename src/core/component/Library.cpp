#include "Library.hpp"

#include "../util/list.hpp"

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
