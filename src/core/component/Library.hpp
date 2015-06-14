#ifndef LIBRARY_HPP
#define LIBRARY_HPP

#include "Component.hpp"

#include <list>

class Library final
{
  public:
    Library();
    ~Library();

    void add(Component *component);
    bool contains(const Component *component) const;
    const std::list<Component *> getComponents() const;
    Component *getComponent(const std::string &name) const;

  private:
    std::list<Component*> components;
};

#endif // LIBRARY_HPP
