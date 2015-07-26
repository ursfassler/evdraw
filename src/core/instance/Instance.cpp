#include "Instance.hpp"
#include "../util/list.hpp"
#include "InstancePortFactory.hpp"

Instance::Instance(const std::string &aName, const Point &aPosition, Component *aComponent) :
  RelativePosition(aPosition),
  name(aName),
  component(aComponent),
  ports()
{
  precondition(component != nullptr);
  component->registerObserver(this);
}

Instance::~Instance()
{
  component->unregisterObserver(this);
}

const std::string &Instance::getName() const
{
  return name;
}

Component *Instance::getComponent() const
{
  return component;
}

void Instance::addPort(AbstractPort *port)
{
  ports.push_back(port);
  ObserverCollection<InstanceObserver>::notify(&InstanceObserver::portAdded, port);
}

void Instance::deletePort(AbstractPort *port)
{
  const auto itr = std::find(ports.begin(), ports.end(), port);
  precondition(itr != ports.end());
  ports.erase(itr);
  ObserverCollection<InstanceObserver>::notify(&InstanceObserver::portDeleted, port);
  delete port;
}

const std::vector<AbstractPort *> &Instance::getPorts() const
{
  return ports;
}

AbstractPort *Instance::getPort(const std::string &name) const
{
  auto predicate = [&](AbstractPort *itr){
    return itr->getName() == name;
  };
  return listGet<AbstractPort*>(ports.begin(), ports.end(), predicate);
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
  InstancePort *instPort = InstancePortFactory::produce(this, port);
  addPort(instPort);
}

void Instance::portDeleted(ComponentPort *port)
{
  auto predicate = [&](AbstractPort *itr){
    return itr->getName() == port->getName();
  };
  auto idx = std::find_if(ports.begin(), ports.end(), predicate);
  precondition(idx != ports.end());
  deletePort(*idx);
}
