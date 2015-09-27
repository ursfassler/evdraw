// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "ImplementationFactory.hpp"

#include "CompositionFactory.hpp"

#include "../util/contract.hpp"
#include "../visitor/NullVisitor.hpp"

class CompositionDisposer :
    public NullVisitor
{
  public:
    void visit(Composition &composition) override
    {
      CompositionFactory::cleanup(composition);
    }

};

void ImplementationFactory::dispose(AbstractImplementation *implementation)
{
  precondition(implementation != nullptr);

  CompositionDisposer disposer;

  implementation->accept(disposer);

  delete implementation;
}
