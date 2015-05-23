#ifndef INSTANCE_HPP
#define INSTANCE_HPP

#include "Component.hpp"

class Instance final
{
  public:
    Instance(Component *aComponent);

    Component *getComponent() const;

  private:
    Component * const component;
};

#endif // INSTANCE_HPP
