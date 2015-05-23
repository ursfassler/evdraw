#ifndef INSTANCEAPPEARANCE_HPP
#define INSTANCEAPPEARANCE_HPP

#include "Component.hpp"
#include "InstancePort.hpp"
#include "types.hpp"

class InstanceAppearance final
{
  public:
    InstanceAppearance(const Component *aComponent);

    PaperUnit width() const;
    PaperUnit height() const;
    PaperUnit portWidth(const InstancePort *port) const;

  private:
    const Component * const component;
};


#endif // INSTANCEAPPEARANCE_HPP
