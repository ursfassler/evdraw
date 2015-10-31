// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef ICOMPONENTINSTANCE
#define ICOMPONENTINSTANCE

#include "IInstance.hpp"

#include "../component/IComponent.hpp"

#include <string>

class IComponentInstance :
    public virtual IInstance
{
  public:
    virtual const std::string &getName() const = 0;
    virtual void setName(const std::string &value) = 0;
    virtual IComponent *getComponent() const = 0;
};

#endif // ICOMPONENTINSTANCE

