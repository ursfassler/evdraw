// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "InstancePort.hpp"

#include "ConnectorFactory.hpp"
#include "../component/InstanceAppearance.hpp"
#include "../util/list.hpp"

#include <stdexcept>

InstancePort::InstancePort(IInstance *aInstance, ComponentPort *aCompPort) :
  RelativePosition(calcOffset(aCompPort)),
  owner(aInstance),
  compPort(aCompPort),
  connector(Point(0,0))
{
  precondition(aInstance != nullptr);
  precondition(aCompPort != nullptr);

  connector.replaceAnchor(this);
  updateConnectorOffset();

  compPort->registerObserver(this);
}

InstancePort::~InstancePort()
{
  compPort->unregisterObserver(this);
  ConnectorFactory::cleanup(connector);
}

Connector &InstancePort::getConnector()
{
  return connector;
}

ComponentPort *InstancePort::getCompPort() const
{
  return compPort;
}

std::string InstancePort::getName() const
{
  return compPort->getName();
}

Point InstancePort::getPosition() const
{
  return getAbsolutePosition();
}

IInstance *InstancePort::getInstance() const
{
  return owner;
}

PortType InstancePort::getType() const
{
  return compPort->getType();
}

void InstancePort::addConnectionPoint(RelativePosition *point)
{
  connector.addPoint(point);
}

void InstancePort::removeConnectionPoint(RelativePosition *point)
{
  connector.removePoint(point);
}

void InstancePort::accept(Visitor &visitor)
{
  visitor.visit(*this);
}

void InstancePort::accept(ConstVisitor &visitor) const
{
  visitor.visit(*this);
}

void InstancePort::topIndexChanged(size_t)
{
  updateOffset();
}

void InstancePort::typeChanged(PortType)
{
  updateOffset();
  updateConnectorOffset();
}

void InstancePort::nameChanged(const std::string &name)
{
  ObserverCollection<InstancePortObserver>::notify<const std::string &>(&InstancePortObserver::nameChanged, name);
}

Point InstancePort::calcOffset(const ComponentPort *compPort)
{
  const Side side = sideOf(compPort->getType());
  switch (side) {
    case Side::Left: {
        return InstanceAppearance::leftPortPosition(compPort->getTopIndex());
      }
    case Side::Right: {
        return InstanceAppearance::rightPortPosition(compPort->getTopIndex());
      }
  }

  throw std::runtime_error("reached unreachable position");
}

void InstancePort::updateOffset()
{
  const Point offset = calcOffset(compPort);
  setOffset(offset);
}

void InstancePort::updateConnectorOffset()
{
  const Side side = sideOf(compPort->getType());;
  const Point conOfs = connectorOffset(side);
  connector.setOffset(conOfs);
}

Point InstancePort::connectorOffset(Side side) const
{
  const int sideMul = side == Side::Left ? -1 : 1;
  const PaperUnit offset = sideMul * InstanceAppearance::portWidth() / 2;
  return Point(offset, 0);
}


InstancePortObserver::~InstancePortObserver()
{
}

void InstancePortObserver::nameChanged(const std::string &)
{
}
