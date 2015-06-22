#ifndef COMPONENTPORT_HPP
#define COMPONENTPORT_HPP

#include "../types.hpp"
#include "../visitor/VisitorClient.hpp"

#include <string>

class ComponentPort : public VisitorClient
{
  public:
    ComponentPort(const std::string &name);

    const std::string &getName() const;

    size_t getTopIndex() const;
    void setTopIndex(size_t value);

  private:
    std::string name;
    size_t topIndex = 0;
};

class Signal final : public ComponentPort
{
  public:
    Signal(const std::string &name);

    void accept(Visitor &visitor);
    void accept(ConstVisitor &visitor) const;

};

class Slot final : public ComponentPort
{
  public:
    Slot(const std::string &name);

    void accept(Visitor &visitor);
    void accept(ConstVisitor &visitor) const;

};

#endif // COMPONENTPORT_HPP
