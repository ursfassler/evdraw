#include "ObserverTest.hpp"

#include "Observer.hpp"
#include "contract.hpp"

class ObservedClass : public ObserverCollection<ObservedClass>
{
  public:
    void notify()
    {
      notifyObservers(this);
    }
};

class ObserverClass : public Observer<ObservedClass>
{
  public:
    void notify(const ObservedClass *sender)
    {
      lastSender = sender;
    }

    ObservedClass const * lastSender = nullptr;
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
