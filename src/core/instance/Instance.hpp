#ifndef INSTANCE_HPP
#define INSTANCE_HPP

#include "../component/Component.hpp"
#include "../util/Observer.hpp"
#include "../Point.hpp"
#include "../base/Position.hpp"

#include "AbstractInstance.hpp"
#include "../connection/AbstractPort.hpp"
#include "../visitor/VisitorClient.hpp"

#include <string>
#include <vector>

class InstanceFactory;

class InstanceObserver
{
  public:
    virtual ~InstanceObserver()
    {
    }

    virtual void portAdded(AbstractPort *port)
    {
      (void)(port);
    }

    virtual void portDeleted(AbstractPort *port)
    {
      (void)(port);
    }
};

class Instance final : public AbstractInstance, public RelativePosition, public VisitorClient, public ObserverCollection<InstanceObserver>, public ComponentObserver
{
  public:
    Instance(const std::string &name, const Point &aPosition, Component *aComponent);
    Instance(const Instance &copy) = delete;
    Instance & operator=(const Instance &) = delete;
    ~Instance();

    const std::string &getName() const;
    Component *getComponent() const;

    const std::vector<AbstractPort *> &getPorts() const;
    AbstractPort *getPort(const std::string &name) const;

    void accept(Visitor &visitor);
    void accept(ConstVisitor &visitor) const;

  protected:
    void portAdded(ComponentPort *port);
    void portDeleted(ComponentPort *port);

  private:
    std::string name;
    Component * const component;
    std::vector<AbstractPort*> ports;

    void addPort(AbstractPort *port);
    void deletePort(AbstractPort *port);

    friend InstanceFactory;

};

#endif // INSTANCE_HPP
