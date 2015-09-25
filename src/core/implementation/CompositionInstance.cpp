#include "CompositionInstance.hpp"

#include "../util/contract.hpp"
#include "../util/list.hpp"

CompositionInstance::CompositionInstance(IComponent *aComponent) :
  component{aComponent},
  ports{}
{
  precondition(component != nullptr);

  for (ComponentPort * cport : aComponent->getPorts()) {
    InstancePort *iport = new InstancePort(this, cport);
    ports.push_back(iport);
  }

  component->registerObserver(this);
}

CompositionInstance::~CompositionInstance()
{
  component->unregisterObserver(this);

  for (InstancePort * port : ports) {
    delete port;
  }
  ports.clear();
}

const std::string &CompositionInstance::getName() const
{
  //TODO return correct name
  static std::string name;
  return name;
}

IComponent *CompositionInstance::getComponent() const
{
  return component;
}

PaperUnit CompositionInstance::getWidth() const
{
  return width;
}

void CompositionInstance::setWidth(PaperUnit value)
{
  width = value;
}

PaperUnit CompositionInstance::getHeight() const
{
  return height;
}

void CompositionInstance::setHeight(PaperUnit value)
{
  height = value;
}

const std::vector<InstancePort *> &CompositionInstance::getPorts() const
{
  return ports;
}

void CompositionInstance::accept(Visitor &visitor)
{
  //TODO implement
  (void)(visitor);
  throw std::runtime_error("not yet implemented");
}

void CompositionInstance::accept(ConstVisitor &visitor) const
{
  //TODO implement
  (void)(visitor);
  throw std::runtime_error("not yet implemented");
}

void CompositionInstance::portAdded(ComponentPort *port)
{
  InstancePort *iport = new InstancePort(this, port);
  ports.push_back(iport);
}

void CompositionInstance::portDeleted(ComponentPort *port)
{
  auto predicate = [&](InstancePort *itr){
    return itr->getCompPort() == port;
  };
  auto idx = std::find_if(ports.begin(), ports.end(), predicate);
  precondition(idx != ports.end());

  InstancePort *instPort = *idx;
  delete instPort;
  ports.erase(idx);
}
