// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef INSTANCEPORT_HPP
#define INSTANCEPORT_HPP

#include "AbstractInstance.hpp"
#include "Connector.hpp"
#include "../connection/AbstractPort.hpp"

#include "../component/ComponentPort.hpp"
#include "../types.hpp"
#include "../base/Position.hpp"

#include <vector>

//TODO connector point position is not updated if point is removed

class InstancePortObserver
{
  public:
    virtual ~InstancePortObserver();

    virtual void nameChanged(const std::string &name);
};

class InstancePort final :
    public AbstractPort,
    public RelativePosition,
    public ObserverCollection<InstancePortObserver>,
    private ComponentPortObserver
{
  public:
    InstancePort(AbstractInstance *instance, ComponentPort *compPort);
    ~InstancePort();

    InstancePort(const InstancePort &) = delete;
    bool operator=(const InstancePort &) = delete;

    ComponentPort *getCompPort() const;
    Connector &getConnector();
    std::string getName() const;
    Point getPosition() const;
    AbstractInstance *getInstance() const;
    PortType getType() const;

    void addConnectionPoint(RelativePosition *point);
    void removeConnectionPoint(RelativePosition *point);

    void accept(Visitor &visitor);
    void accept(ConstVisitor &visitor) const;

  private:
    AbstractInstance * const owner;
    ComponentPort * const compPort;
    Connector connector;

    static Point calcOffset(const ComponentPort *compPort);
    void updateOffset();
    void updateConnectorOffset();
    Point connectorOffset(Side side) const;

    void topIndexChanged(size_t index);
    void typeChanged(PortType);
    void nameChanged(const std::string &name);
};

#endif // INSTANCEPORT_HPP
