// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef LISTOBSERVERMOCK_H
#define LISTOBSERVERMOCK_H

#include <core/util/List.hpp>

#include <vector>

template<class T>
class ListObserverMock :
    public ListObserver<T>
{
  public:

    virtual void added(T* value) override
    {
      addedValue.push_back(value);
    }
    std::vector<T*> addedValue{};

    virtual void removed(T* value) override
    {
      removedValue.push_back(value);
    }
    std::vector<T*> removedValue{};

};

#endif // LISTOBSERVERMOCK_H
