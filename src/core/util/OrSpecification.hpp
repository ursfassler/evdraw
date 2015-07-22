#ifndef ORSPECIFICATION_HPP
#define ORSPECIFICATION_HPP

#include "DefaultSpecification.hpp"

#include <list>

class OrSpecificationTest;

class OrSpecification : public DefaultSpecification
{
  public:
    OrSpecification();
    OrSpecification(const OrSpecification &copy) = delete;
    ~OrSpecification();
    void operator=(const OrSpecification &) = delete;

    bool isSatisfiedBy(const Base *candidate) const;

    void add(const Specification *spec);

  private:
    std::list<const Specification*> specs;

    friend OrSpecificationTest;
};

#endif // ORSPECIFICATION_HPP
