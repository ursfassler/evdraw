#include "CompositionInstance.hpp"

#include "../util/contract.hpp"
#include "../util/list.hpp"
#include "../util/error.hpp"

CompositionInstance::CompositionInstance(IComponent *aComponent) :
  component{aComponent}
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
  //TODO use a minimum width (size as if normal instances)
  if (width != value) {
    width = value;
    notify(&InstanceObserver::widthChanged);
  }
}

PaperUnit CompositionInstance::getHeight() const
{
  return height;
}

void CompositionInstance::setHeight(PaperUnit value)
{
  //TODO use a minimum height (size as if normal instances)
  if (height != value) {
    height = value;
    notify(&InstanceObserver::heightChanged);
  }
}

const std::vector<InstancePort *> &CompositionInstance::getPorts() const
{
  return ports;
}

Side CompositionInstance::portSide(PortType type) const
{
  return getComponent()->portSide(type);
}

Side CompositionInstance::connectorSide(PortType type) const
{
  switch (type) {
  case PortType::Signal:
    return Side::Left;
  case PortType::Slot:
    return Side::Right;
  }

  unreachableCode();
}

void CompositionInstance::accept(Visitor &visitor)
{
  (void)(visitor);
  notYetImplemented();
}

void CompositionInstance::accept(ConstVisitor &visitor) const
{
  visitor.visit(*this);
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
