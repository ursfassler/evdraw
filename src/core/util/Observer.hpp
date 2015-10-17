// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef OBSERVED_HPP
#define OBSERVED_HPP

#include "stdlist.hpp"
#include "contract.hpp"

#include <list>
#include <functional>
#include <cassert>

class ObserverTest;

template<class Observer>
class ObserverCollection
{
  public:
    ObserverCollection(const ObserverCollection&) = delete;
    ObserverCollection &operator =(const ObserverCollection&) = delete;

    ObserverCollection() :
      observers()
    {
    }

    virtual ~ObserverCollection()
    {
      //TODO remove all observer
      precondition(observers.empty());
    }

    bool hasObserver() const
    {
      return !observers.empty();
    }

    bool containsObserver(const Observer *observer) const
    {
      return contains(observers.begin(), observers.end(), observer);
    }

    void registerObserver(Observer *observer)
    {
      precondition(observer != nullptr);
      precondition(!containsObserver(observer));

      observers.push_back(observer);
      //TODO notify observer about registration
    }

    void unregisterObserver(Observer *observer)
    {
      precondition(observer != nullptr);
      precondition(containsObserver(observer));

      observers.remove(observer);
      //TODO notify observer about unregistration
    }

  protected:
    template<class... Args >
    void notify(void (Observer::*method)(Args...), Args... args)
    {
      auto f = std::mem_fn(method);
      for (Observer* itr : observers) {
        f(itr, args...);
      }
    }

  private:
    std::list<Observer*> observers;

    friend ObserverTest;
};

#endif // OBSERVED_HPP
