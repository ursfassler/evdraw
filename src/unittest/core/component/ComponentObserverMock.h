// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef COMPONENTOBSERVERMOCK_H
#define COMPONENTOBSERVERMOCK_H

#include <core/component/Component.hpp>

class ComponentObserverMock : public ComponentObserver
{
  public:
    void maxPortCountChanged() override
    {
      changedHeights++;
    }

    void nameChanged(const std::string &name) override
    {
      newName.push_back(name);
    }

    unsigned changedHeights{0};
    std::vector<std::string> newName{};
};


#endif // COMPONENTOBSERVERMOCK_H
