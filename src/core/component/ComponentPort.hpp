#ifndef COMPONENTPORT_HPP
#define COMPONENTPORT_HPP

#include "../types.hpp"
#include "../visitor/Visitor.hpp"

#include <string>

class ComponentPort final : public VisitorClient
{
  public:
    ComponentPort(const std::string &name);

    const std::string &getName() const;

    size_t getTopIndex() const;
    void setTopIndex(size_t value);

    void accept(Visitor &visitor) const;

  private:
    std::string name;
    size_t topIndex = 0;
};

#endif // COMPONENTPORT_HPP
