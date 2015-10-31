// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef INSTANCEFACTORY_HPP
#define INSTANCEFACTORY_HPP

#include "Instance.hpp"

#include "../component/Component.hpp"

#include "../types.hpp"

#include <string>

class InstanceFactory
{
  public:
    static Instance *produce(IComponent *component, const std::string &name, const Point &position);
    static void cleanup(IComponentInstance &instance);
    static void dispose(IComponentInstance *instance);

  private:
    static void cleanupPort(List<InstancePort> &ports);

};

#endif // INSTANCEFACTORY_HPP
