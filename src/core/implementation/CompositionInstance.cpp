#include "CompositionInstance.hpp"

#include "../util/contract.hpp"
#include "../util/stdlist.hpp"
#include "../util/error.hpp"

CompositionInstance::CompositionInstance(IComponent *aComponent) :
  component{aComponent},
  ports{}
{
  precondition(component != nullptr);

  for (ComponentPort * cport : aComponent->getPorts()) {
    InstancePort *iport = new InstancePort(this, cport);
    ports.add(iport);
  }

  component->getPorts().registerObserver(this);
  component->registerObserver(this);
}

CompositionInstance::~CompositionInstance()
{
  component->unregisterObserver(this);
  component->getPorts().unregisterObserver(this);

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

const List<InstancePort> &CompositionInstance::getPorts() const
{
  return ports;
}

List<InstancePort> &CompositionInstance::getPorts()
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
  visitor.visit(*this);
}

void CompositionInstance::accept(ConstVisitor &visitor) const
{
  visitor.visit(*this);
}

void CompositionInstance::added(ComponentPort *port)
{
  InstancePort *iport = new InstancePort(this, port);
  ports.add(iport);
}

void CompositionInstance::removed(ComponentPort *port)
{
  auto predicate = [&](const InstancePort *itr){
    return itr->getCompPort() == port;
  };
  InstancePort *instPort = ports.get(predicate);
  ports.remove(instPort);
}

void CompositionInstance::nameChanged(IComponent *)
{
  notify<IInstance *>(&InstanceObserver::nameChanged, this);
}
