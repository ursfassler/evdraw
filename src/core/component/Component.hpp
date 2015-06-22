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

    void addPortLeft(Slot *port);
    void addPortRight(Signal *port);

    const std::vector<Slot *> &getPortLeft() const;
    const std::vector<Signal *> &getPortRight() const;

    Side sideOf(const ComponentPort *port) const;

    const std::string &getName() const;

    void accept(Visitor &visitor);
    void accept(ConstVisitor &visitor) const;

    AbstractImplementation *getImplementation() const;
    void setImplementation(AbstractImplementation *value);

  private:
    std::string name;
    std::vector<Slot *> portLeft;
    std::vector<Signal *> portRight;

    AbstractImplementation *implementation;

    friend ComponentFactory;

};

#endif // COMPONENT_HPP
