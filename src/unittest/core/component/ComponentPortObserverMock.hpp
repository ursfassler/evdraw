#ifndef COMPONENTPORTOBSERVERMOCK
#define COMPONENTPORTOBSERVERMOCK

#include <core/component/ComponentPortObserver.hpp>

class ComponentPortObserverMock final :
    public ComponentPortObserver
{
  public:

    std::vector<size_t> newIndex{};
    void topIndexChanged(size_t index) override final
    {
      newIndex.push_back(index);
    }

    std::vector<const ComponentPort *> nameChanged_port{};
    void nameChanged(ComponentPort *port) override final
    {
      nameChanged_port.push_back(port);
    }

    std::vector<const ComponentPort *> typeChanged_port{};
    void typeChanged(ComponentPort *port) override final
    {
      typeChanged_port.push_back(port);
    }
};


#endif // COMPONENTPORTOBSERVERMOCK

