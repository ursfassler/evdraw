#ifndef CHILDREMOVER_HPP
#define CHILDREMOVER_HPP

#include "../specification/Specification.hpp"
#include "../visitor/DefaultVisitor.hpp"

#include <list>

class ChildRemover : public DefaultVisitor
{
  public:
    ChildRemover(const Specification &specification);

    void visit(Composition &composition);

  private:
    const Specification &specification;

    void removeInstances(Composition &composition) const;
    void removeConnections(Composition &composition) const;

    template<class T>
    std::list<T*> getSatisfied(const std::list<T*> &list) const
    {
      std::list<T*> removable;
      for (T *itr : list)
      {
        if (specification.isSatisfiedBy(itr))
        {
          removable.push_back(itr);
        }
      }
      return removable;
    }

};

#endif // CHILDREMOVER_HPP