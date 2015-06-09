#include "ComponentTest.hpp"

#include <core/component/Component.hpp>
#include <core/component/ComponentPort.hpp>
#include <core/component/ComponentFactory.hpp>

void ComponentTest::produce()
{
  Component comp("Lala");
  CPPUNIT_ASSERT_EQUAL(std::string("Lala"), comp.getName());
}

void ComponentTest::addPortLeft()
{
  Component     comp("");
  ComponentPort *port = new ComponentPort("left1");

  CPPUNIT_ASSERT_EQUAL(size_t(0), comp.getPortLeft().size());
  comp.addPortLeft(port);
  CPPUNIT_ASSERT_EQUAL(size_t(1), comp.getPortLeft().size());
  CPPUNIT_ASSERT_EQUAL(size_t(0), port->getTopIndex());
  CPPUNIT_ASSERT_EQUAL(port, comp.getPortLeft()[0]);

  ComponentFactory::cleanup(comp);
}

void ComponentTest::addPortRight()
{
  Component     comp("");
  ComponentPort *port = new ComponentPort("right1");

  CPPUNIT_ASSERT_EQUAL(size_t(0), comp.getPortRight().size());
  comp.addPortRight(port);
  CPPUNIT_ASSERT_EQUAL(size_t(1), comp.getPortRight().size());
  CPPUNIT_ASSERT_EQUAL(size_t(0), port->getTopIndex());
  CPPUNIT_ASSERT_EQUAL(port, comp.getPortRight()[0]);

  ComponentFactory::cleanup(comp);
}

void ComponentTest::rightPortIndexUpdatedOnAdd()
{
  Component     comp("");
  ComponentPort *port1 = new ComponentPort("1");
  ComponentPort *port2 = new ComponentPort("2");
  ComponentPort *port3 = new ComponentPort("3");
  ComponentPort *port4 = new ComponentPort("4");

  comp.addPortRight(port1);
  comp.addPortRight(port2);
  comp.addPortRight(port3);
  comp.addPortRight(port4);

  CPPUNIT_ASSERT_EQUAL(size_t(0), port1->getTopIndex());
  CPPUNIT_ASSERT_EQUAL(size_t(1), port2->getTopIndex());
  CPPUNIT_ASSERT_EQUAL(size_t(2), port3->getTopIndex());
  CPPUNIT_ASSERT_EQUAL(size_t(3), port4->getTopIndex());

  ComponentFactory::cleanup(comp);
}

void ComponentTest::leftPortIndexUpdatedOnAdd()
{
  Component     comp("");
  ComponentPort *port1 = new ComponentPort("1");
  ComponentPort *port2 = new ComponentPort("2");
  ComponentPort *port3 = new ComponentPort("3");
  ComponentPort *port4 = new ComponentPort("4");

  comp.addPortLeft(port1);
  comp.addPortLeft(port2);
  comp.addPortLeft(port3);
  comp.addPortLeft(port4);

  CPPUNIT_ASSERT_EQUAL(size_t(0), port1->getTopIndex());
  CPPUNIT_ASSERT_EQUAL(size_t(1), port2->getTopIndex());
  CPPUNIT_ASSERT_EQUAL(size_t(2), port3->getTopIndex());
  CPPUNIT_ASSERT_EQUAL(size_t(3), port4->getTopIndex());

  ComponentFactory::cleanup(comp);
}

void ComponentTest::portIsLeft()
{
  Component     comp("");
  ComponentPort *port = new ComponentPort("");
  comp.addPortLeft(port);

  CPPUNIT_ASSERT_EQUAL(Side::Left, comp.sideOf(port));

  ComponentFactory::cleanup(comp);
}

void ComponentTest::portIsRight()
{
  Component     comp("");
  ComponentPort *port = new ComponentPort("");
  comp.addPortRight(port);

  CPPUNIT_ASSERT_EQUAL(Side::Right, comp.sideOf(port));

  ComponentFactory::cleanup(comp);
}

void ComponentTest::defaultImplementationIsNullImplementation()
{
  Component     component("");
  CPPUNIT_ASSERT(dynamic_cast<NullImplementation*>(component.getImplementation()) != nullptr);
}

void ComponentTest::constructWithOwnImplementation()
{
  NullImplementation *impl = new NullImplementation();
  Component     component("", impl);
  CPPUNIT_ASSERT_EQUAL(static_cast<AbstractImplementation*>(impl), component.getImplementation());
}

class DeleteTest : public AbstractImplementation
{
  public:
    DeleteTest(bool &aDeleted) :
      deleted(aDeleted)
    {
    }

    ~DeleteTest()
    {
      deleted = true;
    }

    bool &deleted;
};

void ComponentTest::componentDeletesImplementationWhenDeleted()
{
  bool deleted = false;
  DeleteTest *test = new DeleteTest(deleted);
  Component *comp = new Component("", test);
  delete comp;
  CPPUNIT_ASSERT(deleted);
}

void ComponentTest::setImplementation()
{
  Component comp("");
  NullImplementation *impl = new NullImplementation();

  CPPUNIT_ASSERT(static_cast<AbstractImplementation*>(impl) != comp.getImplementation());
  comp.setImplementation(impl);
  CPPUNIT_ASSERT_EQUAL(static_cast<AbstractImplementation*>(impl), comp.getImplementation());
}

void ComponentTest::setImplementationDeletesOldOne()
{
  bool deleted = false;
  DeleteTest *test = new DeleteTest(deleted);
  Component comp("", test);

  comp.setImplementation(new NullImplementation());
  CPPUNIT_ASSERT(deleted);
}
