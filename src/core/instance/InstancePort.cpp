// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "InstancePort.hpp"

#include "ConnectorFactory.hpp"
#include "../component/InstanceAppearance.hpp"
#include "../util/list.hpp"

#include <stdexcept>

InstancePort::InstancePort(IInstance *aInstance, ComponentPort *aCompPort) :
  RelativePosition(Point(0,0)),
  owner(aInstance),
  compPort(aCompPort),
  connector(Point(0,0))
{
  precondition(aInstance != nullptr);
  precondition(aCompPort != nullptr);

  connector.replaceAnchor(this);
  setOffset(calcOffset(compPort));
  updateConnectorOffset();

  compPort->registerObserver(this);
  owner->registerObserver(this);
}

InstancePort::~InstancePort()
{
  owner->unregisterObserver(this);
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

void InstancePort::widthChanged()
{
  updateOffset();
}

Point InstancePort::calcOffset(const ComponentPort *compPort) const
{
  const auto width = getInstance()->getWidth();
  const auto xDist = InstanceAppearance::portOverlap() + (width - InstanceAppearance::portWidth()) / 2;
  const auto side = getInstance()->portSide(compPort->getType());
  const auto xOffset = side == Side::Left ? -xDist : xDist;
  const auto yOffset = InstanceAppearance::portVerticalOffset(compPort->getTopIndex());
  return Point(xOffset, yOffset);
}

void InstancePort::updateOffset()
{
  const Point offset = calcOffset(compPort);
  setOffset(offset);
}

void InstancePort::updateConnectorOffset()
{
  const Side side = getInstance()->connectorSide(compPort->getType());;
  const Point conOfs = connectorOffset(side);
  connector.setOffset(conOfs);
}

Point InstancePort::connectorOffset(Side side) const
{
  const int sideMul = side == Side::Left ? -1 : 1;
  const PaperUnit offset = sideMul * InstanceAppearance::portWidth() / 2;
  return Point(offset, 0);
}

void InstancePort::accept(Visitor &visitor)
{
  visitor.visit(*this);
}

void InstancePort::accept(ConstVisitor &visitor) const
{
  visitor.visit(*this);
}



InstancePortObserver::~InstancePortObserver()
{
}

void InstancePortObserver::nameChanged(const std::string &)
{
}
