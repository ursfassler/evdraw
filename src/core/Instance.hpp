#ifndef INSTANCE_HPP
#define INSTANCE_HPP

#include "Component.hpp"
#include "types.hpp"

class Instance final
{
  public:
    Instance(PaperUnit aX, PaperUnit aY, Component *aComponent);

    Component *getComponent() const;

    PaperUnit getX() const;
    PaperUnit getY() const;

  private:
    PaperUnit x;
    PaperUnit y;
    Component * const component;
};

#endif // INSTANCE_HPP
