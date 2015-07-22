#ifndef VISITORCLIENT_HPP
#define VISITORCLIENT_HPP

#include "ConstVisitor.hpp"
#include "Visitor.hpp"
#include "../base/Base.hpp"

class VisitorClient : public Base
{
  public:
    virtual ~VisitorClient() {}
    virtual void accept(Visitor &visitor) = 0;
    virtual void accept(ConstVisitor &visitor) const = 0;
};


#endif // VISITORCLIENT_HPP
