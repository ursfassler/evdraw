#ifndef INSTANCEAPPEARANCE_HPP
#define INSTANCEAPPEARANCE_HPP

#include "Component.hpp"
#include "ComponentPort.hpp"
#include "types.hpp"

class InstanceAppearance final
{
  public:
    InstanceAppearance(const Component *aComponent);

    PaperUnit width() const;
    PaperUnit height() const;
    PaperUnit portWidth() const;
    PaperUnit portHeight() const;
    PaperUnit leftPortXOffset() const;
    PaperUnit leftPortYOffset(const ComponentPort *port) const;
    PaperUnit rightPortXOffset() const;
    PaperUnit rightPortYOffset(const ComponentPort *port) const;

  private:
    const Component * const component;

    PaperUnit scale(int value) const;
    unsigned indexOf(const ComponentPort *port, const std::vector<ComponentPort*> &list) const;
    PaperUnit portOffset(unsigned index) const;
};

#endif // INSTANCEAPPEARANCE_HPP
