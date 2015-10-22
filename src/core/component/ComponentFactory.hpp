// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef COMPONENTFACTORY_HPP
#define COMPONENTFACTORY_HPP

#include "Component.hpp"

#include <string>
#include <vector>

class ComponentFactory
{
  public:
    static Component *produce(const std::string &name);
    static Component *produce(const std::string &name, const std::vector<std::string> &inPort, const std::vector<std::string> &outPort);

    static void cleanup(IComponent &component);
    static void dispose(IComponent *component);
};

#endif // COMPONENTFACTORY_HPP
