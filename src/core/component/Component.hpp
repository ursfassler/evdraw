#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include "ComponentPort.hpp"
#include "AbstractImplementation.hpp"
#include "../types.hpp"
#include "../visitor/Visitor.hpp"

#include <vector>
#include <string>

class ComponentFactory;

class Component final : public VisitorClient
{
  public:
    Component(const std::string &name);
    Component(const std::string &name, AbstractImplementation *implementation);
    ~Component();

    void addPortLeft(ComponentPort *port);
    void addPortRight(ComponentPort *port);

    const std::vector<ComponentPort *> &getPortLeft() const;
    const std::vector<ComponentPort *> &getPortRight() const;

    Side sideOf(const ComponentPort *port) const;

    const std::string &getName() const;

    void accept(Visitor &visitor) const;

    AbstractImplementation *getImplementation();

  private:
    std::string name;
    std::vector<ComponentPort *> portLeft;
    std::vector<ComponentPort *> portRight;

    AbstractImplementation * const implementation;

    friend ComponentFactory;

};

#endif // COMPONENT_HPP
