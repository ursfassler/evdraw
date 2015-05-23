#ifndef OBSERVED_HPP
#define OBSERVED_HPP

#include <list>
#include <functional>
#include <cassert>

template<typename Sender, typename Listener>
class Observed
{
  public:
    Observed(const Observed &copy) = delete;
    Observed & operator=(const Observed &L) = delete;

    Observed(const Sender * aSender) :
      listeners(),
      sender(aSender)
    {
    }

    virtual ~Observed()
    {
      assert(listeners.empty());
    }

    bool hasListener() const
    {
      return !listeners.empty();
    }

    void addListener(Listener *listener)
    {
      assert(listener != nullptr);
//      assert(listeners.find(listener) == listeners.end());

      listeners.push_back(listener);
    }

    void removeListener(Listener *listener)
    {
      assert(listener != nullptr);
//      assert(listeners.find(listener) != listeners.end());

      listeners.remove(listener);
    }

  public:

    typedef void (Listener::*Notifier) (const Sender*);

    template<Notifier F>
    void notifyListeners()
    {
      for (Listener *itr : listeners) {
        (itr->*F)(sender);
      }
    }

  private:
    std::list<Listener*> listeners;
    const Sender * sender;
};

#endif // OBSERVED_HPP
