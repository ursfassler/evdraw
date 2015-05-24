#ifndef INSTANCE_HPP
#define INSTANCE_HPP

#include "../component/Component.hpp"
#include "../util/Observer.hpp"
#include "../Point.hpp"
#include "../base/Base.hpp"

class Instance final : public Base
{
  public:
    Instance(const Point &aPosition, Component *aComponent);
    Instance(const Instance &copy) = delete;
    Instance & operator=(const Instance &L) = delete;

    Component *getComponent() const;

  private:
    Component * const component;
};

#endif // INSTANCE_HPP
