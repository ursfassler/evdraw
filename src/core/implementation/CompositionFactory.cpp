// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "CompositionFactory.hpp"

#include <core/util/contract.hpp>
#include <core/connection/ConnectionFactory.hpp>


void CompositionFactory::cleanup(Composition &composition)
{
  precondition(composition.selfInstance != nullptr);
  precondition(composition.selfInstance->containsObserver(&composition));

  while (!composition.connections.empty()) {
    composition.deleteConnection(composition.connections.back());
  }

  if (composition.connectionUnderConstruction != nullptr) {
    ConnectionFactory::dispose(composition.connectionUnderConstruction);
    composition.connectionUnderConstruction = nullptr;
  }

  while (!composition.instances.empty()) {
    composition.deleteInstance(composition.instances.back());
  }

  composition.selfInstance->unregisterObserver(&composition);
  delete composition.selfInstance;
  composition.selfInstance = nullptr;

  postcondition(composition.connections.empty());
  postcondition(composition.instances.empty());
  postcondition(composition.connectionUnderConstruction == nullptr);
  postcondition(composition.selfInstance == nullptr);
}

void CompositionFactory::dispose(Composition *composition)
{
  precondition(composition != nullptr);

  cleanup(*composition);
  delete composition;
}
