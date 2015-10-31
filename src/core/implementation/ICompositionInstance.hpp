// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef ICOMPOSITIONINSTANCE
#define ICOMPOSITIONINSTANCE

#include "../instance/IInstance.hpp"
#include "../component/IComponent.hpp"

class ICompositionInstance :
    public virtual IInstance
{
  public:
    virtual ~ICompositionInstance(){}

    virtual IComponent *getComponent() const = 0;

    virtual PaperUnit getWidth() const = 0;
    virtual void setWidth(PaperUnit value) = 0;
    virtual PaperUnit getHeight() const = 0;
    virtual void setHeight(PaperUnit value) = 0;

    virtual const List<InstancePort> &getPorts() const = 0;
    virtual List<InstancePort> &getPorts() = 0;
};

#endif // ICOMPOSITIONINSTANCE

