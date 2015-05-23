#ifndef OBSERVED_HPP
#define OBSERVED_HPP

#include <list>
#include <functional>

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
    }

    bool hasListener() const
    {
      return !listeners.empty();
    }

    void addListener(Listener *listener)
    {
      listeners.push_back(listener);
    }

    void removeListener(Listener *listener)
    {
      listeners.remove(listener);
    }

  protected:

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
