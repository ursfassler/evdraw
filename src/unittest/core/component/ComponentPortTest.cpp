#include "ComponentPortTest.hpp"

#include <core/component/ComponentPort.hpp>

#include <string>

class TestComponentPort : public ComponentPort
{
  public:
    TestComponentPort(bool &mDestructorCalled) :
      ComponentPort(""),
      destructorCalled(mDestructorCalled)
    {
    }

    ~TestComponentPort()
    {
      destructorCalled = true;
    }

    Side side() const
    {
      return Side::Left;
    }

    virtual void accept(Visitor &)
    {
    }

    virtual void accept(ConstVisitor &) const
    {
    }

  private:
    bool &destructorCalled;
};

void ComponentPortTest::destructor_is_virtual()
{
  bool destructorCalled = false;
  ComponentPort *port = new TestComponentPort(destructorCalled);
  delete port;

  CPPUNIT_ASSERT(destructorCalled);
}

void ComponentPortTest::name()
{
  Signal port("hallo");
  CPPUNIT_ASSERT_EQUAL(std::string("hallo"), port.getName());
  CPPUNIT_ASSERT_EQUAL(size_t(0), port.getTopIndex());
}

void ComponentPortTest::setTopIndex()
{
  Signal port("hallo");
  port.setTopIndex(42);
  CPPUNIT_ASSERT_EQUAL(size_t(42), port.getTopIndex());
}


void SignalTest::produce()
{
  Signal port("hallo");

  CPPUNIT_ASSERT_EQUAL(std::string("hallo"), port.getName());
  CPPUNIT_ASSERT_EQUAL(size_t(0), port.getTopIndex());
}

void SignalTest::portIsRight()
{
  Signal port("");

  CPPUNIT_ASSERT_EQUAL(Side::Right, port.side());
}



void SlotTest::produce()
{
  Slot port("hallo");

  CPPUNIT_ASSERT_EQUAL(std::string("hallo"), port.getName());
  CPPUNIT_ASSERT_EQUAL(size_t(0), port.getTopIndex());
}

void SlotTest::portIsLeft()
{
  Slot port("");

  CPPUNIT_ASSERT_EQUAL(Side::Left, port.side());
}

