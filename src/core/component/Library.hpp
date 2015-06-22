#ifndef LIBRARY_HPP
#define LIBRARY_HPP

#include "Component.hpp"
#include "../visitor/VisitorClient.hpp"

#include <vector>

class Library final : public VisitorClient
{
  public:
    Library();
    ~Library();

    void add(Component *component);
    bool contains(const Component *component) const;
    const std::vector<Component *> getComponents() const;
    Component *getComponent(const std::string &name) const;

    void accept(Visitor &visitor);
    void accept(ConstVisitor &visitor) const;

  private:
    std::vector<Component*> components;
};

#endif // LIBRARY_HPP
