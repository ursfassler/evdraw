#ifndef CHILDREMOVER_HPP
#define CHILDREMOVER_HPP

#include "Specification.hpp"
#include "../visitor/DefaultVisitor.hpp"

class ChildRemover : public DefaultVisitor
{
  public:
    ChildRemover(const Specification &specification);

    void visit(Composition &composition);

  private:
    const Specification &specification;

};

#endif // CHILDREMOVER_HPP
