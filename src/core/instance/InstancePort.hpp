#ifndef INSTANCEPORT_HPP
#define INSTANCEPORT_HPP

#include "Connector.hpp"

#include "Instance.hpp"

#include "../component/ComponentPort.hpp"
#include "../types.hpp"
#include "../base/Base.hpp"

#include <vector>

class InstancePort final : public AbstractPort, public Positionable
{
  public:
    InstancePort(Instance *instance, ComponentPort *compPort, const Point &offset);

    InstancePort(const InstancePort &) = delete;
    bool operator=(const InstancePort &) = delete;

    ComponentPort *getCompPort() const;
    Connector &getConnector();
    const std::string &getName() const;
    Instance *getInstance() const;

    void addConnectionPoint(Positionable *point);
    void removeConnectionPoint(Positionable *point);

  private:
    Instance * const owner;
    ComponentPort * const compPort;
    Connector connector;

};

#endif // INSTANCEPORT_HPP
