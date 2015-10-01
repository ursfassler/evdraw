#ifndef COMPONENTMOCK
#define COMPONENTMOCK

#include <core/component/Component.hpp>

class ComponentMock: public IComponent
{
  public:
    const std::string &getName() const override
    {
      static const std::string name;
      return name;
    }

    const std::vector<ComponentPort *> &getPorts() const override
    {
      static std::vector<ComponentPort *> ports;
      return ports;
    }

    Side portSide(PortType) const override
    {
      return Side::Left;
    }
};

#endif // COMPONENTMOCK

