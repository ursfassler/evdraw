#ifndef INSTANCE_HPP
#define INSTANCE_HPP

#include "../component/Component.hpp"
#include "../util/Observed.hpp"
#include "../types.hpp"

class Instance;

class InstanceListener
{
  public:
    virtual ~InstanceListener();
    virtual void positionChange(const Instance *sender);
};

class Instance final : public Observed<Instance, InstanceListener>
{
  public:
    Instance(const Point &aPosition, Component *aComponent);
    Instance(const Instance &copy) = delete;
    Instance & operator=(const Instance &L) = delete;

    Component *getComponent() const;

    Point getPosition() const;
    void setPosition(const Point &value);

  private:
    Point position;
    Component * const component;


};

#endif // INSTANCE_HPP
