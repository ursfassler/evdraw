// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef CHILDREMOVER_HPP
#define CHILDREMOVER_HPP

#include "../specification/Specification.hpp"
#include "../visitor/DefaultVisitor.hpp"
#include "../util/List.hpp"

class ChildRemover : public DefaultVisitor
{
  public:
    ChildRemover(const Specification &specification);

    void visit(Composition &composition);

  private:
    const Specification &specification;

    void deleteInstances(Composition &composition) const;
    void deleteConnections(Composition &composition) const;

    template<class T>
    std::vector<T*> getSatisfied(const List<T> &list) const
    {
      const auto predicate = [&](const T *instance) -> bool {
        return specification.isSatisfiedBy(instance);
      };
      return list.getAll(predicate);
    }

};

#endif // CHILDREMOVER_HPP
