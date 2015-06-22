#ifndef ABSTRACTIMPLEMENTATION_HPP
#define ABSTRACTIMPLEMENTATION_HPP

#include "../visitor/VisitorClient.hpp"

class AbstractImplementation : public VisitorClient
{
  public:
    virtual ~AbstractImplementation() {}
};

#endif // ABSTRACTIMPLEMENTATION_HPP
