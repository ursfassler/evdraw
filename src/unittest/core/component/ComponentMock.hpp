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
    void setName(const std::string &value) override
    {
      name = value;
    }
    std::string name{};

    const List<ComponentPort> &getPorts() const override
    {
      return ports;
    }

    List<ComponentPort> &getPorts() override
    {
      return ports;
    }
    List<ComponentPort> ports{};

    Side portSide(PortType) const override
    {
      return Side::Left;
    }

    size_t maxPortCount() const override
    {
      return {};
    }

    IImplementation *getImplementation() const override
    {
      return implementation;
    }
    IImplementation *implementation{};

    void notify_nameChange()
    {
      notify<IComponent*>(&ComponentObserver::nameChanged, this);
    }

    void accept(Visitor &) override
    {
    }

    void accept(ConstVisitor &) const override
    {
    }

};

#endif // COMPONENTMOCK

