#ifndef COMPONENTMOCK
#define COMPONENTMOCK

#include <core/component/Component.hpp>

class ComponentMock: public IComponent
{
  public:
    const std::vector<ComponentPort *> &getPorts() const override
    {
      static std::vector<ComponentPort *> ports;
      return ports;
    }
};

#endif // COMPONENTMOCK

