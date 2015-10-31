#include "InstanceMock.hpp"


InstanceMock::InstanceMock(bool *aDestroyed) :
  destroyed{aDestroyed}
{
}

InstanceMock::~InstanceMock()
{
  if (destroyed != nullptr) {
    *destroyed = true;
  }
}

const List<InstancePort> &InstanceMock::getPorts() const
{
  return ports;
}

List<InstancePort> &InstanceMock::getPorts()
{
  return ports;
}

Side InstanceMock::portSide(PortType) const
{
  return Side::Left;
}

Side InstanceMock::connectorSide(PortType) const
{
  return Side::Left;
}

PaperUnit InstanceMock::getWidth() const
{
  return {};
}

PaperUnit InstanceMock::getHeight() const
{
  return {};
}

void InstanceMock::accept(Visitor &)
{
}

void InstanceMock::accept(ConstVisitor &) const
{
}
