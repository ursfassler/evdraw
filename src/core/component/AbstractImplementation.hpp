#ifndef ABSTRACTIMPLEMENTATION_HPP
#define ABSTRACTIMPLEMENTATION_HPP

#include "../visitor/Visitor.hpp"

class AbstractImplementation : public VisitorClient
{
  public:
    virtual ~AbstractImplementation() {}
};

#endif // ABSTRACTIMPLEMENTATION_HPP
