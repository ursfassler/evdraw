#include "ObserverTest.hpp"

#include "Observer.hpp"
#include "contract.hpp"

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

#include <iostream>
#include <array>

class Test
{
  public:
    virtual ~Test()
    {
    }

    virtual void test()
    {
      std::cout << "Test::test" << std::endl;
    }

    virtual void foo(const std::string msg)
    {
      std::cout << "Test::foo: " << msg << std::endl;
    }
};

class TestA : public Test
{
  public:
    void test()
    {
      std::cout << "TestA::test" << std::endl;
    }

    std::array<int,10> array;
};

class TestB : public Test
{
  public:
    void foo(const std::string msg)
    {
      std::cout << "TestB::foo: " << msg << std::endl;
    }

    int num = 42;
};

void ObserverTest::functr()
{
  ObserverCollection<Test> obscol;
  Test observer;
  TestA obsA;
  TestB obsB;
  obscol.registerObserver(&observer);
  obscol.registerObserver(&obsA);
  obscol.registerObserver(&obsB);

  obscol.notify(&Test::test);
  obscol.notify(&Test::foo, std::string("Hallo"));

  obscol.unregisterObserver(&obsB);
  obscol.unregisterObserver(&obsA);
  obscol.unregisterObserver(&observer);
}

