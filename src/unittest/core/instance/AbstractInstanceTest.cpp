// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "AbstractInstanceTest.hpp"

#include <core/instance/AbstractInstance.hpp>
#include <core/base/Base.hpp>
#include <core/base/Position.hpp>

class TestAbstractInstance : public AbstractInstance
{
  public:
    TestAbstractInstance(bool &aDestroyed) :
      AbstractInstance(Point(0,0)),
      destroyed(aDestroyed)
    {
    }

    ~TestAbstractInstance()
    {
      destroyed = true;
    }

    const std::string &getName() const
    {
      static const std::string name("test");
      return name;
    }

    void accept(Visitor &)
    {
    }

    void accept(ConstVisitor &) const
    {
    }

  private:
    bool &destroyed;

};

void AbstractInstanceTest::setUp()
{
  destroyed = false;
  instance = new TestAbstractInstance(destroyed);
}

void AbstractInstanceTest::tearDown()
{
  delete instance;
  instance = nullptr;
}

void AbstractInstanceTest::destructorIsVirtual()
{
  bool destroyed = false;
  AbstractInstance *instance = new TestAbstractInstance(destroyed);
  delete instance;
  CPPUNIT_ASSERT(destroyed);
}

void AbstractInstanceTest::inheritsVisitorClient()
{
  CPPUNIT_ASSERT(dynamic_cast<VisitorClient*>(instance) != nullptr);
}

void AbstractInstanceTest::inheritsPosition()
{
  CPPUNIT_ASSERT(dynamic_cast<Position*>(instance) != nullptr);
}

void AbstractInstanceTest::hasGetName()
{
  CPPUNIT_ASSERT_EQUAL(std::string("test"), instance->getName());
}
