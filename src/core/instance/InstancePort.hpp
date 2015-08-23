#ifndef INSTANCEPORT_HPP
#define INSTANCEPORT_HPP

#include "AbstractInstance.hpp"
#include "Connector.hpp"
#include "../connection/AbstractPort.hpp"

#include "../component/ComponentPort.hpp"
#include "../types.hpp"
#include "../base/Position.hpp"

#include <vector>

class InstancePortObserver
{
  public:
    virtual ~InstancePortObserver()
    {
    }

    virtual void nameChanged(const std::string &name)
    {
      (void)(name);
    }
};

class InstancePort final :
    public AbstractPort,
    public RelativePosition,
    public ObserverCollection<InstancePortObserver>,
    protected ComponentPortObserver
{
  public:
    InstancePort(AbstractInstance *instance, ComponentPort *compPort, const Point &offset);
    ~InstancePort();

    InstancePort(const InstancePort &) = delete;
    bool operator=(const InstancePort &) = delete;

    ComponentPort *getCompPort() const;
    Connector &getConnector();
    void setName(const std::string &name);
    std::string getName() const;
    Point getPosition() const;
    AbstractInstance *getInstance() const;
    Side side() const;

    void addConnectionPoint(RelativePosition *point);
    void removeConnectionPoint(RelativePosition *point);

    void accept(Visitor &visitor);
    void accept(ConstVisitor &visitor) const;

  protected:
    void topIndexChanged(size_t index);
    void nameChanged(const std::string &name);

  private:
    AbstractInstance * const owner;
    ComponentPort * const compPort;
    Connector connector;

    Point calcOffset() const;
};

#endif // INSTANCEPORT_HPP
