// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef INSTANCE_HPP
#define INSTANCE_HPP

#include "../component/Component.hpp"
#include "../util/Observer.hpp"
#include "../Point.hpp"

#include "AbstractInstance.hpp"
#include "InstancePort.hpp"
#include "../visitor/VisitorClient.hpp"

#include <string>
#include <vector>

class InstanceFactory;

class InstanceObserver
{
  public:
    virtual ~InstanceObserver()
    {
    }

    virtual void portAdded(InstancePort *port)
    {
      (void)(port);
    }

    virtual void portDeleted(InstancePort *port)
    {
      (void)(port);
    }
};

class Instance final : public AbstractInstance, public ObserverCollection<InstanceObserver>, public ComponentObserver
{
  public:
    Instance(const std::string &name, const Point &aPosition, Component *aComponent);
    Instance(const Instance &copy) = delete;
    Instance & operator=(const Instance &) = delete;
    ~Instance();

    const std::string &getName() const;
    Component *getComponent() const;

    const std::vector<InstancePort *> &getPorts() const;
    InstancePort *getPort(const std::string &name) const;

    void accept(Visitor &visitor);
    void accept(ConstVisitor &visitor) const;

  protected:
    void portAdded(ComponentPort *port);
    void portDeleted(ComponentPort *port);

  private:
    std::string name;
    Component * const component;
    std::vector<InstancePort*> ports;

    void addPort(InstancePort *port);
    void deletePort(InstancePort *port);

    friend InstanceFactory;

};

#endif // INSTANCE_HPP
