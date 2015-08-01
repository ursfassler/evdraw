#include "Component.hpp"

#include "../util/list.hpp"
#include "../util/contract.hpp"

#include <map>

Component::Component(const std::string &aName, AbstractImplementation *aImplementation) :
  name(aName),
  ports(),
  implementation(aImplementation)
{
}

Component::~Component()
{
  delete implementation;
}

void Component::addPort(ComponentPort *port)
{
  ports.push_back(port);
  updateTopIndex();
  notify(&ComponentObserver::portAdded, port);
}

void Component::deletePort(ComponentPort *port)
{
  std::vector<ComponentPort*>::iterator idx = std::find(ports.begin(), ports.end(), port);
  precondition(idx != ports.end());
  ports.erase(idx);
  updateTopIndex();
  notify(&ComponentObserver::portDeleted, port);
  delete port;
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
    index[port->side()]++;
  }

  return std::max(index[Side::Left], index[Side::Right]);
}

const std::string &Component::getName() const
{
  return name;
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
    size_t &portIndex = index[port->side()];
    port->setTopIndex(portIndex);
    portIndex++;
  }
}
