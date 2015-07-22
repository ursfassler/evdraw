#ifndef DEFAULTSPECIFICATION_HPP
#define DEFAULTSPECIFICATION_HPP

#include "Specification.hpp"

class DefaultSpecification : public Specification
{
  public:
    Specification *or_(const Specification *right) const;

};

#endif // DEFAULTSPECIFICATION_HPP
