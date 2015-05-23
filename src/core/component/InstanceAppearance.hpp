#ifndef INSTANCEAPPEARANCE_HPP
#define INSTANCEAPPEARANCE_HPP

#include "Component.hpp"
#include "ComponentPort.hpp"
#include "../types.hpp"

class InstanceAppearance final
{
  public:
    static PaperUnit width();
    static PaperUnit height(const Component &component);
    static PaperUnit portWidth();
    static PaperUnit portHeight();
    static PaperUnit leftPortXOffset();
    static PaperUnit leftPortYOffset(const Component &component, const ComponentPort *port);
    static PaperUnit rightPortXOffset();
    static PaperUnit rightPortYOffset(const Component &component, const ComponentPort *port);

  private:
    static PaperUnit scale(int value);
    static PaperUnit portOffset(unsigned index);
};

#endif // INSTANCEAPPEARANCE_HPP
