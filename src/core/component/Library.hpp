#ifndef LIBRARY_HPP
#define LIBRARY_HPP

#include "Component.hpp"

#include <list>

class Library final
{
  public:
    ~Library();

    void add(Component *component);
    bool contains(const Component *component) const;



  private:
    std::list<Component*> components;
};

#endif // LIBRARY_HPP
