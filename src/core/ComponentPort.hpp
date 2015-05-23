#ifndef COMPONENTPORT_HPP
#define COMPONENTPORT_HPP

#include <string>

class ComponentPort final
{
  public:
    ComponentPort(const std::string &aName);

    const std::string &getName() const;

  private:
    std::string name;
};

#endif // COMPONENTPORT_HPP
