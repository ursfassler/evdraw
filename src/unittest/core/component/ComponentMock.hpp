#ifndef COMPONENTMOCK
#define COMPONENTMOCK

#include <core/component/Component.hpp>

class ComponentMock: public IComponent
{
  public:
    const std::string &getName() const override
    {
      return name;
    }

    const List<ComponentPort> &getPorts() const override
    {
      return ports;
    }

    List<ComponentPort> &getPorts() override
    {
      return ports;
    }

    Side portSide(PortType) const override
    {
      return Side::Left;
    }

    const std::string name{};
    List<ComponentPort> ports{};
};

#endif // COMPONENTMOCK

