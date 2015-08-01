#ifndef INSTANCEFACTORY_HPP
#define INSTANCEFACTORY_HPP

#include "Instance.hpp"

#include "../component/Component.hpp"

#include "../types.hpp"

#include <string>

class InstanceFactory
{
  public:
    static Instance *produce(Component *component, const std::string &name, const Point &position);
    static void cleanup(Instance &instance);
    static void dispose(Instance *instance);

  private:
    static void cleanupPort(std::vector<InstancePort *> &ports);

};

#endif // INSTANCEFACTORY_HPP
