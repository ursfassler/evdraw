// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "Component.hpp"

#include "../util/stdlist.hpp"
#include "../util/contract.hpp"
#include "../util/error.hpp"

#include <map>

Component::Component(const std::string &aName, IImplementation *aImplementation) :
  name{aName},
  ports{},
  implementation{aImplementation}
{
  ports.registerObserver(this);
}

Component::~Component()
{
  precondition(implementation == nullptr);
  ports.unregisterObserver(this);
}

void Component::added(ComponentPort *port)
{
  port->registerObserver(this);
  updateTopIndex();

  const auto count = maxPortCount();
  if (count != oldCount) {
    oldCount = count;
    notify(&ComponentObserver::maxPortCountChanged);
  }
}

void Component::removed(ComponentPort *port)
{
  updateTopIndex();
  port->unregisterObserver(this);

  const auto count = maxPortCount();
  if (count != oldCount) {
    notify(&ComponentObserver::maxPortCountChanged);
    oldCount = count;
  }
}

const List<ComponentPort> &Component::getPorts() const
{
  return ports;
}

List<ComponentPort> &Component::getPorts()
{
  return ports;
}

ComponentPort *Component::getPort(const std::string &name) const
{
  auto predicate = [&](const ComponentPort *itr){
    return itr->getName() == name;
  };
  return ports.get(predicate);
}

size_t Component::maxPortCount() const
{
  std::map<Side,size_t> index;
  index[Side::Left] = 0;
  index[Side::Right] = 0;

  for (ComponentPort *port : ports) {
    const Side side = portSide(port->getType());
    index[side]++;
  }

  return std::max(index[Side::Left], index[Side::Right]);
}

const std::string &Component::getName() const
{
  return name;
}

void Component::setName(const std::string &value)
{
  if (name != value) {
    name = value;
    notify<IComponent*>(&ComponentObserver::nameChanged, this);
  }
}

void Component::accept(Visitor &visitor)
{
  visitor.visit(*this);
}

void Component::accept(ConstVisitor &visitor) const
{
  visitor.visit(*this);
}

IImplementation *Component::getImplementation() const
{
  return implementation;
}

void Component::setImplementation(IImplementation *value)
{
  precondition(value != nullptr);

  delete implementation;
  implementation = value;
}

void Component::updateTopIndex()
{
  std::map<Side,size_t> index;
  index[Side::Left] = 0;
  index[Side::Right] = 0;

  for (ComponentPort *port : ports) {
    const Side side = portSide(port->getType());
    size_t &portIndex = index[side];
    port->setTopIndex(portIndex);
    portIndex++;
  }
}

void Component::typeChanged(ComponentPort *)
{
  updateTopIndex();
  //TODO do only notify if height really changed
  notify(&ComponentObserver::maxPortCountChanged);
}

Side Component::portSide(PortType type) const
{
  switch (type) {
    case PortType::Signal:
      return Side::Right;
    case PortType::Slot:
      return Side::Left;
  }

  unreachableCode();
}
