// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "Component.hpp"

#include "../util/list.hpp"
#include "../util/contract.hpp"
#include "../util/error.hpp"

#include <map>

Component::Component(const std::string &aName, AbstractImplementation *aImplementation) :
  name(aName),
  ports(),
  implementation(aImplementation)
{
}

Component::~Component()
{
  precondition(implementation == nullptr);
}

void Component::addPort(ComponentPort *port)
{
  const size_t oldHeight = height();
  ports.push_back(port);
  port->registerObserver(this);
  updateTopIndex();
  notify(&ComponentObserver::portAdded, port);
  if (height() != oldHeight) {
    notify(&ComponentObserver::heightChanged);
  }
}

void Component::deletePort(ComponentPort *port)
{
  std::vector<ComponentPort*>::iterator idx = std::find(ports.begin(), ports.end(), port);
  precondition(idx != ports.end());

  const size_t oldHeight = height();
  port->unregisterObserver(this);
  ports.erase(idx);
  updateTopIndex();
  notify(&ComponentObserver::portDeleted, port);
  delete port;
  if (height() != oldHeight) {
    notify(&ComponentObserver::heightChanged);
  }
}

const std::vector<ComponentPort *> &Component::getPorts() const
{
  return ports;
}

ComponentPort *Component::getPort(const std::string &name) const
{
  auto predicate = [&](ComponentPort *itr){
    return itr->getName() == name;
  };
  return listGet<ComponentPort*>(ports.begin(), ports.end(), predicate);
}

size_t Component::height() const
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
    notify<const std::string &>(&ComponentObserver::nameChanged, value);
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

AbstractImplementation *Component::getImplementation() const
{
  return implementation;
}

void Component::setImplementation(AbstractImplementation *value)
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

void Component::typeChanged(PortType)
{
  updateTopIndex();
  //TODO do only notify if height really changed
  notify(&ComponentObserver::heightChanged);
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



ComponentObserver::~ComponentObserver()
{
}

void ComponentObserver::portAdded(ComponentPort *)
{
}

void ComponentObserver::portDeleted(ComponentPort *)
{
}

void ComponentObserver::heightChanged()
{
}

void ComponentObserver::nameChanged(const std::string &)
{
}
