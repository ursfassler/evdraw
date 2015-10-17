#ifndef LIST_H
#define LIST_H

#include "Observer.hpp"

#include <cstdint>
#include <vector>
#include <algorithm>
#include <functional>

/**
 * List takes ownership of pointed to objects.
 * If such an object is removed from the list, it will be deleted.
 * Adding and removing elements can be observed.
 */

template<class T>
class ListObserver
{
  public:
    virtual ~ListObserver() = default;

    virtual void added(T*)
    {
    }

    virtual void removed(T*)
    {
    }
};

template<class T>
class List final :
    public ObserverCollection<ListObserver<T>>
{
  public:
    typedef std::function<void(T* disposal)> Disposer;

    List(const Disposer &aDisposer = defaultDisposer, const std::initializer_list<T*> &init = {}) :
      disposer(aDisposer),
      values{init}
    {
      if (doubled(init)) {
        throw std::invalid_argument("items are only allowed to bi in list once");
      }
    }

    List(const std::initializer_list<T*> &init) :
      disposer{defaultDisposer},
      values{init}
    {
      if (doubled(init)) {
        throw std::invalid_argument("items are only allowed to bi in list once");
      }
    }

    ~List()
    {
      clear();
    }

    std::size_t size() const
    {
      return values.size();
    }

    bool empty() const
    {
      return size() == 0;
    }

    bool contains(const T* value) const
    {
      const auto idx = std::find(values.begin(), values.end(), value);
      return idx != values.end();
    }

    T* operator[](size_t index) const
    {
      return values[index];
    }

    template<typename R>
    size_t indexOf(R value) const
    {
      size_t idx = 0;
      for (const T* itr : values) {
        if (itr == value) {
          return idx;
        }
        idx++;
      }

      throw std::invalid_argument("element not in list");
    }

    void add(T* value)
    {
      if (contains(value)) {
        throw std::invalid_argument("already in list");
      }
      values.push_back(value);
      this->notify(&ListObserver<T>::added, value);
    }

    void remove(T* value)
    {
      while (true) {
        const auto idx = std::find(values.begin(), values.end(), value);
        if (idx == values.end()) {
          return;
        }

        values.erase(idx);
        this->notify(&ListObserver<T>::removed, value);
        disposer(value);
      }
    }

    void clear()
    {
      while (!values.empty()) {
        remove(values.back());
      }
    }

    std::vector<T*> getAll(std::function<bool(const T* value)> predicate) const
    {
      std::vector<T*> ret;

      for (T* itr : values) {
        if (predicate(itr)) {
          ret.push_back(itr);
        }
      }

      return ret;
    }

    T* get(std::function<bool(const T* value)> predicate) const
    {
      for (T* itr : values) {
        if (predicate(itr)) {
          return itr;
        }
      }

      throw std::invalid_argument("element not in list");
    }

    T* front() const
    {
      return values.front();
    }

    T* back() const
    {
      return values.back();
    }

    typedef typename std::vector<T*>::const_iterator const_iterator;

    const_iterator begin() const
    {
      return values.begin();
    }

    const_iterator end() const
    {
      return values.end();
    }

  private:
    Disposer disposer;
    std::vector<T*>  values{};

    static void defaultDisposer(T* value)
    {
      delete value;
    }

    bool doubled(const std::initializer_list<T*> &values) const
    {
      for (auto itr = values.begin(); itr != values.end(); itr++) {
        for (auto check = itr+1; check != values.end(); check++) {
          if (*itr == *check) {
            return true;
          }
        }
      }

      return false;
    }

};

#endif // LIST_H
