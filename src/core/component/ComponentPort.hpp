// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef COMPONENTPORT_HPP
#define COMPONENTPORT_HPP

#include "PortType.hpp"
#include "ComponentPortObserver.hpp"
#include "../types.hpp"
#include "../visitor/VisitorClient.hpp"
#include "../util/Observer.hpp"

#include <string>


class ComponentPort final :
  public VisitorClient,
  public ObserverCollection<ComponentPortObserver>
{
  public:
    ComponentPort(const std::string &name, PortType type);
    ~ComponentPort();

    const std::string &getName() const;
    void setName(const std::string &name);

    size_t getTopIndex() const;
    void setTopIndex(size_t value);

    PortType getType() const;
    void setType(PortType value);

    void accept(Visitor &visitor);
    void accept(ConstVisitor &visitor) const;

  private:
    std::string name;
    PortType type;
    size_t topIndex = 0;
};

#endif // COMPONENTPORT_HPP
