// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

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

    virtual void componentAdded(Component *component)
    {
      (void)(component);
    }

    virtual void componentDeleted(Component *component)
    {
      (void)(component);
    }
};

class Library final : public VisitorClient, public ObserverCollection<LibraryObserver>
{
  public:
    Library();
    ~Library();

    void addComponent(Component *component);
    void deleteComponent(Component *component);
    bool contains(const Component *component) const;
    const std::vector<Component *> getComponents() const;
    Component *getComponent(const std::string &name) const;

    void accept(Visitor &visitor);
    void accept(ConstVisitor &visitor) const;

  private:
    std::vector<Component*> components;
};

#endif // LIBRARY_HPP
