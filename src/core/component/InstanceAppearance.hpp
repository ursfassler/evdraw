#ifndef INSTANCEAPPEARANCE_HPP
#define INSTANCEAPPEARANCE_HPP

#include "Component.hpp"
#include "ComponentPort.hpp"
#include "../types.hpp"
#include "../Point.hpp"

class InstanceAppearance final
{
  public:
    static PaperUnit width();
    static PaperUnit height(const Component &component);
    static PaperUnit portWidth();
    static PaperUnit portHeight();
    static Point portDimension();
    static PaperUnit leftPortXOffset();
    static PaperUnit rightPortXOffset();
    static PaperUnit portYOffset(unsigned index);

  private:
    static PaperUnit scale(int value);
};

#endif // INSTANCEAPPEARANCE_HPP
