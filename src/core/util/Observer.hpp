#ifndef OBSERVED_HPP
#define OBSERVED_HPP

#include "list.hpp"
#include "contract.hpp"

#include <list>
#include <functional>
#include <cassert>

template<typename Subject>
class Observer
{
  public:
    virtual ~Observer()
    {
    }

    virtual void notify(const Subject *subject) = 0;
};


template<typename Subject>
class ObserverCollection
{
  public:
    ObserverCollection() :
      observers()
    {
    }

    virtual ~ObserverCollection()
    {
      assert(observers.empty());
    }

    bool hasObserver() const
    {
      return !observers.empty();
    }

    bool containsObserver(const Observer<Subject> *observer) const
    {
      return contains(observers.begin(), observers.end(), observer);
    }

    void registerObserver(Observer<Subject> *observer)
    {
      precondition(observer != nullptr);
      precondition(!containsObserver(observer));

      observers.push_back(observer);
    }

    void unregisterObserver(Observer<Subject> *observer)
    {
      precondition(observer != nullptr);
      precondition(containsObserver(observer));

      observers.remove(observer);
    }

  protected:
    void notifyObservers(const Subject *subject) const
    {
      for (Observer<Subject> *itr : observers) {
        itr->notify(subject);
      }
    }

  private:
    std::list<Observer<Subject>*> observers;
};

#endif // OBSERVED_HPP
