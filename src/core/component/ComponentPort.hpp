#ifndef COMPONENTPORT_HPP
#define COMPONENTPORT_HPP

#include "../types.hpp"
#include "../visitor/VisitorClient.hpp"
#include "../util/Observer.hpp"

#include <string>

class ComponentPortObserver
{
  public:
    virtual ~ComponentPortObserver()
    {
    }

    virtual void topIndexChanged(size_t index)
    {
      (void)(index);
    }

    virtual void nameChanged(const std::string &name)
    {
      (void)(name);
    }

};

class ComponentPort : public VisitorClient, public ObserverCollection<ComponentPortObserver>
{
  public:
    ComponentPort(const std::string &name);

    const std::string &getName() const;
    void setName(const std::string &name);

    size_t getTopIndex() const;
    void setTopIndex(size_t value);

    virtual Side side() const = 0;

  private:
    std::string name;
    size_t topIndex = 0;
};

class Signal final : public ComponentPort
{
  public:
    Signal(const std::string &name);

    Side side() const;

    void accept(Visitor &visitor);
    void accept(ConstVisitor &visitor) const;

};

class Slot final : public ComponentPort
{
  public:
    Slot(const std::string &name);

    Side side() const;

    void accept(Visitor &visitor);
    void accept(ConstVisitor &visitor) const;

};

#endif // COMPONENTPORT_HPP
