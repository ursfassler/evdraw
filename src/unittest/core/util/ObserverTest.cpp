#include "ObserverTest.hpp"

#include <core/util/Observer.hpp>
#include <core/util/contract.hpp>

class ObservedClass;

class ObserverClass
{
  public:
    void notify(ObservedClass *sender)
    {
      lastSender = sender;
    }

    ObservedClass const * lastSender = nullptr;
};

class ObservedClass : public ObserverCollection<ObserverClass>
{
  public:
    void call()
    {
      notify(&ObserverClass::notify, this);
    }
};

void ObserverTest::addRemoveObserver()
{
  ObservedClass observed;
  ObserverClass observer;

  CPPUNIT_ASSERT(!observed.hasObserver());
  CPPUNIT_ASSERT(!observed.containsObserver(&observer));

  observed.registerObserver(&observer);
  CPPUNIT_ASSERT(observed.hasObserver());
  CPPUNIT_ASSERT(observed.containsObserver(&observer));

  observed.unregisterObserver(&observer);
  CPPUNIT_ASSERT(!observed.hasObserver());
  CPPUNIT_ASSERT(!observed.containsObserver(&observer));
}

void ObserverTest::canNotRegisterNullptr()
{
  ObservedClass observed;
  CPPUNIT_ASSERT_THROW(observed.registerObserver(nullptr), PreconditionError);
}

void ObserverTest::canNotUnregisterNullptr()
{
  ObservedClass observed;
  CPPUNIT_ASSERT_THROW(observed.unregisterObserver(nullptr), PreconditionError);
}

void ObserverTest::canNotRegisterTwice()
{
  ObservedClass observed;
  ObserverClass observer;

  observed.registerObserver(&observer);
  CPPUNIT_ASSERT_THROW(observed.registerObserver(&observer), PreconditionError);

  observed.unregisterObserver(&observer);
}

void ObserverTest::needToBeRegisteredToUnregister()
{
  ObservedClass observed;
  ObserverClass observer;

  CPPUNIT_ASSERT_THROW(observed.unregisterObserver(&observer), PreconditionError);
}

class Test
{
  public:
    virtual ~Test()
    {
    }

    virtual void foo()
    {
      lastFoo = "Test::foo";
    }

    virtual void bar()
    {
      lastBar = "Test::bar";
    }

    std::string lastFoo = "";
    std::string lastBar = "";
};

class TestA : public Test
{
  public:
    void bar()
    {
      lastBar = "TestA::bar";
    }
};

class TestB : public Test
{
  public:
    void foo()
    {
      lastFoo = "TestB::foo";
    }
};

void ObserverTest::virtualFunctionDispatch()
{
  ObserverCollection<Test> obscol;

  Test observer;
  TestA obsA;
  TestB obsB;

  obscol.registerObserver(&observer);
  obscol.registerObserver(&obsA);
  obscol.registerObserver(&obsB);

  obscol.notify(&Test::foo);
  obscol.notify(&Test::bar);

  CPPUNIT_ASSERT_EQUAL(std::string("Test::foo"), observer.lastFoo);
  CPPUNIT_ASSERT_EQUAL(std::string("Test::bar"), observer.lastBar);
  CPPUNIT_ASSERT_EQUAL(std::string("Test::foo"), obsA.lastFoo);
  CPPUNIT_ASSERT_EQUAL(std::string("TestA::bar"), obsA.lastBar);
  CPPUNIT_ASSERT_EQUAL(std::string("TestB::foo"), obsB.lastFoo);
  CPPUNIT_ASSERT_EQUAL(std::string("Test::bar"), obsB.lastBar);

  obscol.unregisterObserver(&obsB);
  obscol.unregisterObserver(&obsA);
  obscol.unregisterObserver(&observer);
}

