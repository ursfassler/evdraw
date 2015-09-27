// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "RizzlyPrintTest.hpp"
#include "../core/implementation/CompositionInstanceMock.hpp"

#include <file/RizzlyPrint.hpp>
#include <core/component/ComponentFactory.hpp>
#include <core/instance/InstanceFactory.hpp>
#include <core/connection/ConnectionFactory.hpp>
#include <core/implementation/CompositionFactory.hpp>

#include <sstream>

static std::vector<std::string> asList(std::stringstream &stream)
{
  std::vector<std::string> ret;
  std::string line;
  while (std::getline(stream, line)) {
    ret.push_back(line);
  }
  return ret;
}

void RizzlyPrintTest::printEmpty()
{
  std::stringstream ss;
  RizzlyPrint printer(ss);
  Composition composition{new CompositionInstanceMock()};

  printer.print(composition);

  CPPUNIT_ASSERT_EQUAL(std::string(""), ss.str());

  CompositionFactory::cleanup(composition);
}

void RizzlyPrintTest::onlyInstance()
{
  std::stringstream ss;
  RizzlyPrint printer(ss);
  Component *component = ComponentFactory::produce("Component", {}, {});
  Instance *instance = InstanceFactory::produce(component, "instance", Point(0,0));
  Composition *composition = new Composition(new CompositionInstanceMock());
  composition->addInstance(instance);

  printer.print(*composition);

  std::vector<std::string> listing = asList(ss);
  CPPUNIT_ASSERT_EQUAL(size_t(1), listing.size());
  CPPUNIT_ASSERT_EQUAL(std::string("instance: Component;"), listing[0]);

  CompositionFactory::dispose(composition);
  ComponentFactory::dispose(component);
}

void RizzlyPrintTest::connection()
{
  std::stringstream ss;
  RizzlyPrint printer(ss);
  Component *component = ComponentFactory::produce("Component", {"a"}, {"b"});
  Instance *instance = InstanceFactory::produce(component, "inst", Point(0,0));
  Connection *connection = ConnectionFactory::produce(instance->getPorts().front(), instance->getPorts().back());

  Composition *composition = new Composition(new CompositionInstanceMock());
  composition->addInstance(instance);
  composition->addConnection(connection);

  printer.print(*composition);

  std::vector<std::string> listing = asList(ss);
  CPPUNIT_ASSERT_EQUAL(size_t(2), listing.size());
  CPPUNIT_ASSERT_EQUAL(std::string("inst: Component;"), listing[0]);
  CPPUNIT_ASSERT_EQUAL(std::string("inst.a -> inst.b;"), listing[1]);

  CompositionFactory::dispose(composition);
  ComponentFactory::dispose(component);
}
