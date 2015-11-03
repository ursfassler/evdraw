// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "Instance.hpp"
#include "../util/stdlist.hpp"
#include "../util/error.hpp"
#include "../component/InstanceAppearance.hpp"

Instance::Instance(const std::string &aName, const Point &aPosition, IComponent *aComponent) :
  name{aName},
  component{aComponent},
  position{aPosition},
  ports{}
{
  precondition(component != nullptr);
  component->registerObserver(this);
  component->getPorts().registerObserver(this);
}

Instance::~Instance()
{
  precondition(!ObserverCollection<InstanceObserver>::hasObserver());

  component->getPorts().unregisterObserver(this);
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
    ObserverCollection<InstanceObserver>::notify<IInstance*>(&InstanceObserver::nameChanged, this);
  }
}

IComponent *Instance::getComponent() const
{
  return component;
}

RelativePosition &Instance::getPosition()
{
  return position;
}

const RelativePosition &Instance::getPosition() const
{
  return position;
}

const List<InstancePort> &Instance::getPorts() const
{
  return ports;
}

List<InstancePort> &Instance::getPorts()
{
  return ports;
}

InstancePort *Instance::getPort(const std::string &name) const
{
  auto predicate = [&](const InstancePort *itr){
    return itr->getName() == name;
  };
  return ports.get(predicate);
}

Side Instance::portSide(PortType type) const
{
  return getComponent()->portSide(type);
}

Side Instance::connectorSide(PortType type) const
{
  return portSide(type);
}

PaperUnit Instance::getWidth() const
{
  return InstanceAppearance::componentWidth();
}

PaperUnit Instance::getHeight() const
{
  const size_t count = getComponent()->maxPortCount();
  return (count-1) * InstanceAppearance::verticalPortDistance() +
      InstanceAppearance::topPortDistance() +
      InstanceAppearance::bottomPortDistance();
}

void Instance::accept(Visitor &visitor)
{
  visitor.visit(*this);
}

void Instance::accept(ConstVisitor &visitor) const
{
  visitor.visit(*this);
}

void Instance::added(ComponentPort *port)
{
  InstancePort *instPort = new InstancePort(this, port);
  instPort->getPosition().replaceAnchor(&position);
  ports.add(instPort);
}

void Instance::removed(ComponentPort *port)
{
  auto predicate = [&](const InstancePort *itr){
    return itr->getCompPort() == port;
  };

  const auto instancePort = ports.get(predicate);
  ports.remove(instancePort);
}

void Instance::maxPortCountChanged()
{
  ObserverCollection<InstanceObserver>::notify(&InstanceObserver::heightChanged);
}

void Instance::nameChanged(IComponent *)
{
  ObserverCollection<InstanceObserver>::notify<IInstance*>(&InstanceObserver::componentNameChanged, this);
}
