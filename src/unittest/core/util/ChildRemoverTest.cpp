// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "ChildRemoverTest.hpp"
#include "../implementation/CompositionInstanceMock.hpp"
#include "../connection/PortMock.hpp"

#include <core/util/ChildRemover.hpp>
#include <core/specification/AlwaysSatisfiedSpecification.hpp>
#include <core/implementation/Composition.hpp>
#include <core/implementation/CompositionFactory.hpp>
#include <core/instance/Instance.hpp>
#include <core/visitor/DefaultVisitor.hpp>
#include <core/instance/InstanceFactory.hpp>
#include <core/component/ComponentFactory.hpp>
#include <core/connection/ConnectionFactory.hpp>

void ChildRemoverTest::inheritsDefaultVisitor()
{
  AlwaysSatisfiedSpecification alwaysTrue;
  ChildRemover remover(alwaysTrue);
  CPPUNIT_ASSERT(dynamic_cast<DefaultVisitor*>(&remover) != nullptr);
}

void ChildRemoverTest::compositionRemovesInstance()
{
  Component *component = ComponentFactory::produce("component");
  Instance *instance = InstanceFactory::produce(component, "inst", Point(0,0));
  Composition composition{new CompositionInstanceMock()};
  composition.addInstance(instance);

  AlwaysSatisfiedSpecification alwaysTrue;
  ChildRemover remover(alwaysTrue);

  composition.accept(remover);

  CPPUNIT_ASSERT_EQUAL(size_t(0), composition.getInstances().size());

  ComponentFactory::dispose(component);
  CompositionFactory::cleanup(composition);
}

void ChildRemoverTest::compositionRemovesConnection()
{
  Composition composition{new CompositionInstanceMock()};
  PortMock portA;
  PortMock portB;
  Connection *connection = ConnectionFactory::produce(&portA, &portB);
  composition.addConnection(connection);

  AlwaysSatisfiedSpecification alwaysTrue;
  ChildRemover remover(alwaysTrue);

  composition.accept(remover);

  CPPUNIT_ASSERT_EQUAL(size_t(0), composition.getConnections().size());

  CompositionFactory::cleanup(composition);
}
