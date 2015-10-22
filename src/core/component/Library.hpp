// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef LIBRARY_HPP
#define LIBRARY_HPP

#include "Component.hpp"
#include "../visitor/VisitorClient.hpp"
#include "../util/Observer.hpp"
#include "../util/List.hpp"

#include <vector>

class Library final :
    public VisitorClient,
    private ListObserver<IComponent>
{
  public:
    Library();
    ~Library();

    const List<IComponent> &getComponents() const;
    List<IComponent> &getComponents();
    IComponent *getComponent(const std::string &name) const;

    void accept(Visitor &visitor);
    void accept(ConstVisitor &visitor) const;

  private:
    List<IComponent> components;

    void removed(IComponent* value) override;

};

#endif // LIBRARY_HPP
