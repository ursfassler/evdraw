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

const std::string &InstanceMock::getName() const
{
  static const std::string name("test");
  return name;
}

const std::vector<InstancePort *> &InstanceMock::getPorts() const
{
  static const std::vector<InstancePort *> ports;
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
