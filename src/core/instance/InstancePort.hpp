// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef INSTANCEPORT_HPP
#define INSTANCEPORT_HPP

#include "IInstance.hpp"
#include "InstanceObserver.h"
#include "Connector.hpp"
#include "../connection/IPort.hpp"

#include "../component/ComponentPort.hpp"
#include "../types.hpp"
#include "../base/Position.hpp"

#include <vector>

class InstancePortObserver
{
  public:
    virtual ~InstancePortObserver();

    virtual void nameChanged(const std::string &name);
};

class InstancePort :
    public IPort,
    public RelativePosition,
    public ObserverCollection<InstancePortObserver>,
    private ComponentPortObserver,
    private InstanceObserver
{
  public:
    InstancePort(IInstance *instance, ComponentPort *compPort);
    ~InstancePort();

    InstancePort(const InstancePort &) = delete;
    bool operator=(const InstancePort &) = delete;

    ComponentPort *getCompPort() const;
    Connector &getConnector();
    std::string getName() const override;
    Point getPosition() const override;
    IInstance *getInstance() const;
    PortType getType() const;

    void updateOffset();

    void addConnectionPoint(RelativePosition *point) override;
    void removeConnectionPoint(RelativePosition *point) override;

    void accept(Visitor &visitor) override final;
    void accept(ConstVisitor &visitor) const override final;

  private:
    IInstance * const owner;
    ComponentPort * const compPort;
    Connector connector;

    Point calcOffset(const ComponentPort *compPort) const;
    void updateConnectorOffset();
    Point connectorOffset(Side side) const;

    void topIndexChanged(size_t index) override;
    void typeChanged(PortType) override;
    void nameChanged(const std::string &name) override;

    void widthChanged() override;
};

#endif // INSTANCEPORT_HPP
