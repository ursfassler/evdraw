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

class Instance final : public AbstractInstance, public RelativePosition, public VisitorClient
{
  public:
    Instance(const std::string &name, const Point &aPosition, Component *aComponent);
    Instance(const Instance &copy) = delete;
    Instance & operator=(const Instance &L) = delete;

    const std::string &getName() const;
    Component *getComponent() const;

    void addPort(AbstractPort *port);
    const std::vector<AbstractPort *> &getPorts() const;
    AbstractPort *getPort(const std::string &name) const;

    void accept(Visitor &visitor);
    void accept(ConstVisitor &visitor) const;

  private:
    std::string name;
    Component * const component;
    std::vector<AbstractPort*> ports;

    friend InstanceFactory;

};

#endif // INSTANCE_HPP
