#ifndef INSTANCE_HPP
#define INSTANCE_HPP

#include "../component/Component.hpp"
#include "../util/Observer.hpp"
#include "../Point.hpp"
#include "../base/Base.hpp"

#include "InstancePort.hpp"

#include <string>
#include <vector>

class InstanceFactory;

class Instance final : public Base
{
  public:
    Instance(const std::string &name, const Point &aPosition, Component *aComponent);
    Instance(const Instance &copy) = delete;
    Instance & operator=(const Instance &L) = delete;

    const std::string &getName() const;
    Component *getComponent() const;

    void addInput(InstancePort *port);
    const std::vector<InstancePort *> &getInput() const;

    void addOutput(InstancePort *port);
    const std::vector<InstancePort *> &getOutput() const;

  private:
    std::string name;
    Component * const component;
    std::vector<InstancePort *> input;
    std::vector<InstancePort *> output;

    friend InstanceFactory;

};

#endif // INSTANCE_HPP
