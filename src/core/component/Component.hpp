#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include "ComponentPort.hpp"

#include <vector>

class Component
{
  public:
    Component();

    void addPortLeft(ComponentPort *port);
    void addPortRight(ComponentPort *port);

    const std::vector<ComponentPort *> &getPortLeft() const;
    const std::vector<ComponentPort *> &getPortRight() const;

  private:
    std::vector<ComponentPort *> portLeft;
    std::vector<ComponentPort *> portRight;

};

#endif // COMPONENT_HPP
