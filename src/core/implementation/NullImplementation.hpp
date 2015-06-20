#ifndef NULLIMPLEMENTATION_HPP
#define NULLIMPLEMENTATION_HPP

#include "../component/AbstractImplementation.hpp"

class NullImplementation : public AbstractImplementation
{
  public:
    NullImplementation();

    virtual void accept(Visitor &visitor) const;
};

#endif // NULLIMPLEMENTATION_HPP
