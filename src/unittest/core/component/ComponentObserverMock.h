// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef COMPONENTOBSERVERMOCK_H
#define COMPONENTOBSERVERMOCK_H

#include <core/component/Component.hpp>

class ComponentObserverMock : public ComponentObserver
{
  public:
    unsigned changedHeights{0};
    void maxPortCountChanged() override
    {
      changedHeights++;
    }

    std::vector<IComponent*> nameChanged_item{};
    void nameChanged(IComponent *item) override
    {
      nameChanged_item.push_back(item);
    }

};


#endif // COMPONENTOBSERVERMOCK_H
