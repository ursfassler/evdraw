#ifndef COMPONENTFACTORY_HPP
#define COMPONENTFACTORY_HPP

#include "Component.hpp"

#include <string>
#include <vector>

class ComponentFactory
{
  public:
    static Component *produce(const std::string &name);
    static Component *produce(const std::string &name, const std::vector<std::string> &inPort, const std::vector<std::string> &outPort);

    static void cleanup(Component &component);
    static void dispose(Component *component);
};

#endif // COMPONENTFACTORY_HPP
