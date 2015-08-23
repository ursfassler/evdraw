// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "InstancePort.hpp"

#include "../component/InstanceAppearance.hpp"
#include "../util/list.hpp"

#include <stdexcept>

InstancePort::InstancePort(AbstractInstance *aInstance, ComponentPort *aCompPort, const Point &aOffset) :
  RelativePosition(aOffset),
  owner(aInstance),
  compPort(aCompPort),
  connector(Point(0,0))
{
  precondition(aInstance != nullptr);
  precondition(aCompPort != nullptr);

  replaceAnchor(aInstance);
  connector.replaceAnchor(this);

  compPort->registerObserver(this);
}

InstancePort::~InstancePort()
{
  compPort->unregisterObserver(this);
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

void InstancePort::setName(const std::string &name)
{
  compPort->setName(name);
}

Point InstancePort::getPosition() const
{
  return getAbsolutePosition();
}

AbstractInstance *InstancePort::getInstance() const
{
  return owner;
}

Side InstancePort::side() const
{
  return compPort->side();
}

void InstancePort::addConnectionPoint(RelativePosition *point)
{
  connector.addPoint(point);
}

void InstancePort::removeConnectionPoint(RelativePosition *point)
{
  (void)(point);
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
  const Point offset = calcOffset();
  setOffset(offset);
}

void InstancePort::nameChanged(const std::string &name)
{
  ObserverCollection<InstancePortObserver>::notify<const std::string &>(&InstancePortObserver::nameChanged, name);
}

Point InstancePort::calcOffset() const
{
  switch (compPort->side()) {
    case Side::Left: {
        return InstanceAppearance::leftPortPosition(compPort->getTopIndex());
      }
    case Side::Right: {
        return InstanceAppearance::rightPortPosition(compPort->getTopIndex());
      }
  }

  throw std::runtime_error("reached unreachable position");
}
