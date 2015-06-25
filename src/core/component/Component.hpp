#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include "ComponentPort.hpp"
#include "AbstractImplementation.hpp"
#include "../types.hpp"
#include "../visitor/VisitorClient.hpp"

#include <vector>
#include <string>

class ComponentFactory;

class Component final : public VisitorClient
{
  public:
    Component(const std::string &name, AbstractImplementation *implementation);
    ~Component();

    Component(const Component &) = delete;
    Component operator=(const Component &) = delete;

    void addPort(ComponentPort *port);
    const std::vector<ComponentPort *> &getPorts() const;

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
