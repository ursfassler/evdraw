#ifndef INSTANCEPORT_HPP
#define INSTANCEPORT_HPP

#include "Connector.hpp"

#include "Instance.hpp"

#include "../component/ComponentPort.hpp"
#include "../types.hpp"
#include "../base/Position.hpp"

#include <vector>

class InstancePort final : public AbstractPort, public RelativePosition
{
  public:
    InstancePort(Instance *instance, ComponentPort *compPort, const Point &offset);

    InstancePort(const InstancePort &) = delete;
    bool operator=(const InstancePort &) = delete;

    ComponentPort *getCompPort() const;
    Connector &getConnector();
    std::string getName() const;
    Instance *getInstance() const;
    Side side() const;

    void addConnectionPoint(RelativePosition *point);
    void removeConnectionPoint(RelativePosition *point);

    void accept(Visitor &visitor) const;

  private:
    Instance * const owner;
    ComponentPort * const compPort;
    Connector connector;

};

#endif // INSTANCEPORT_HPP
