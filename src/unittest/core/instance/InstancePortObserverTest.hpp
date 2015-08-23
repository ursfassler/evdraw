#ifndef INSTANCEPORTOBSERVERTEST_HPP
#define INSTANCEPORTOBSERVERTEST_HPP

#include <core/instance/InstancePort.hpp>
#include <core/component/ComponentPort.hpp>

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class DummyInstance : public AbstractInstance
{
  public:
    DummyInstance() :
      AbstractInstance(Point(0,0))
    {
    }

    virtual const std::string &getName() const
    {
      return name;
    }
    const std::string name = "";

    void accept(Visitor &)
    {
    }

    void accept(ConstVisitor &) const
    {
    }

};


class InstancePortObserverTest: public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( InstancePortObserverTest );

    CPPUNIT_TEST(destructor_is_virtual);
    CPPUNIT_TEST(inherits_ObserverCollection);

    CPPUNIT_TEST(notify_on_name_change);

    CPPUNIT_TEST_SUITE_END();

  public:
    void setUp();
    void tearDown();

    void destructor_is_virtual();
    void inherits_ObserverCollection();

    void notify_on_name_change();

  private:
    ComponentPort *component = nullptr;
    DummyInstance *instance = nullptr;
    InstancePort *port = nullptr;

};

CPPUNIT_TEST_SUITE_REGISTRATION( InstancePortObserverTest );

#endif // INSTANCEPORTOBSERVERTEST_HPP
