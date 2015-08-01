#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include "ComponentPort.hpp"
#include "AbstractImplementation.hpp"
#include "../types.hpp"
#include "../visitor/VisitorClient.hpp"
#include "../util/Observer.hpp"

#include <vector>
#include <string>

class ComponentFactory;

class ComponentObserver
{
  public:
    virtual ~ComponentObserver()
    {
    }

    virtual void portAdded(ComponentPort *port)
    {
      (void)(port);
    }

    virtual void portDeleted(ComponentPort *port)
    {
      (void)(port);
    }
};

class Component final : public VisitorClient, public ObserverCollection<ComponentObserver>
{
  public:
    Component(const std::string &name, AbstractImplementation *implementation);
    ~Component();

    Component(const Component &) = delete;
    Component operator=(const Component &) = delete;

    void addPort(ComponentPort *port);
    void deletePort(ComponentPort *port);
    const std::vector<ComponentPort *> &getPorts() const;
    ComponentPort *getPort(const std::string &name) const;

    size_t height() const;

    const std::string &getName() const;

    void accept(Visitor &visitor);
    void accept(ConstVisitor &visitor) const;

    AbstractImplementation *getImplementation() const;
    void setImplementation(AbstractImplementation *value);

  private:
    std::string name;
    std::vector<ComponentPort *> ports;

    AbstractImplementation *implementation;

    void updateTopIndex();

    friend ComponentFactory;

};

#endif // COMPONENT_HPP
