// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "Instance.hpp"
#include "../util/list.hpp"
#include "../util/error.hpp"

Instance::Instance(const std::string &aName, const Point &aPosition, Component *aComponent) :
  AbstractInstance{aPosition},
  name{aName},
  component{aComponent},
  ports{}
{
  precondition(component != nullptr);
  component->registerObserver(this);
}

Instance::~Instance()
{
  precondition(!ObserverCollection<InstanceObserver>::hasObserver());
  precondition(!ObserverCollection<PositionObserver>::hasObserver());

  component->unregisterObserver(this);
}

const std::string &Instance::getName() const
{
  return name;
}

void Instance::setName(const std::string &name)
{
  if (this->name != name) {
    this->name = name;
    ObserverCollection<InstanceObserver>::notify<const Instance*>(&InstanceObserver::nameChanged, this);
  }
}

Component *Instance::getComponent() const
{
  return component;
}

void Instance::addPort(InstancePort *port)
{
  ports.push_back(port);
  ObserverCollection<InstanceObserver>::notify(&InstanceObserver::portAdded, port);
}

void Instance::deletePort(InstancePort *port)
{
  const auto itr = std::find(ports.begin(), ports.end(), port);
  precondition(itr != ports.end());
  ports.erase(itr);
  ObserverCollection<InstanceObserver>::notify(&InstanceObserver::portDeleted, port);
  delete port;
}

const std::vector<InstancePort *> &Instance::getPorts() const
{
  return ports;
}

InstancePort *Instance::getPort(const std::string &name) const
{
  auto predicate = [&](InstancePort *itr){
    return itr->getName() == name;
  };
  return listGet<InstancePort*>(ports.begin(), ports.end(), predicate);
}

Side Instance::portSide(PortType type) const
{
  return getComponent()->portSide(type);
}

Side Instance::connectorSide(PortType type) const
{
  return portSide(type);
}

void Instance::accept(Visitor &visitor)
{
  visitor.visit(*this);
}

void Instance::accept(ConstVisitor &visitor) const
{
  visitor.visit(*this);
}

void Instance::portAdded(ComponentPort *port)
{
  InstancePort *instPort = new InstancePort(this, port);
  instPort->replaceAnchor(this);
  addPort(instPort);
}

void Instance::portDeleted(ComponentPort *port)
{
  auto predicate = [&](InstancePort *itr){
    return itr->getCompPort() == port;
  };
  auto idx = std::find_if(ports.begin(), ports.end(), predicate);
  precondition(idx != ports.end());
  deletePort(*idx);
}

void Instance::heightChanged()
{
  ObserverCollection<InstanceObserver>::notify(&InstanceObserver::heightChanged);
}

void Instance::nameChanged(const std::string &)
{
  ObserverCollection<InstanceObserver>::notify<const Instance*>(&InstanceObserver::componentNameChanged, this);
}


InstanceObserver::~InstanceObserver()
{
}

void InstanceObserver::portAdded(InstancePort *)
{
}

void InstanceObserver::portDeleted(InstancePort *)
{
}

void InstanceObserver::nameChanged(const Instance *)
{
}

void InstanceObserver::componentNameChanged(const Instance *)
{
}

void InstanceObserver::heightChanged()
{
}
