#ifndef LIBRARY_HPP
#define LIBRARY_HPP

#include "Component.hpp"
#include "../visitor/VisitorClient.hpp"
#include "../util/Observer.hpp"

#include <vector>

class LibraryObserver
{
  public:
    virtual ~LibraryObserver()
    {
    }

    virtual void addComponent(const Library *parent, Component *component)
    {
      (void)(parent);
      (void)(component);
    }

    virtual void delComponent(const Library *parent, Component *component)
    {
      (void)(parent);
      (void)(component);
    }
};

class Library final : public VisitorClient, public ObserverCollection<LibraryObserver>
{
  public:
    Library();
    ~Library();

    void add(Component *component);
    void del(Component *component);
    bool contains(const Component *component) const;
    const std::vector<Component *> getComponents() const;
    Component *getComponent(const std::string &name) const;

    void accept(Visitor &visitor);
    void accept(ConstVisitor &visitor) const;

  private:
    std::vector<Component*> components;
};

#endif // LIBRARY_HPP
