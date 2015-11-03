// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "InstanceFactory.hpp"

#include "../util/contract.hpp"

Instance *InstanceFactory::produce(IComponent *component, const std::string &name, const Point &position)
{
  precondition(component != nullptr);

  Instance *instance = new Instance(name, position, component);

  for (ComponentPort *compPort : component->getPorts()) {
    InstancePort *instPort = new InstancePort(instance, compPort);
    instPort->getPosition().replaceAnchor(&instance->getPosition());
    instance->getPorts().add(instPort);
  }

  return instance;
}

void InstanceFactory::cleanup(IComponentInstance &instance)
{
  cleanupPort(instance.getPorts());
  postcondition(instance.getPorts().empty());
}

void InstanceFactory::dispose(IComponentInstance *instance)
{
  precondition(instance != nullptr);

  cleanup(*instance);
  delete instance;
}

void InstanceFactory::cleanupPort(List<InstancePort> &ports)
{
  ports.clear();
}
