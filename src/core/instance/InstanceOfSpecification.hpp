#ifndef INSTANCEOFSPECIFICATION_HPP
#define INSTANCEOFSPECIFICATION_HPP

#include "../specification//DefaultSpecification.hpp"
#include "../component/Component.hpp"
#include "../base/Base.hpp"

class InstanceOfSpecificationTest;

class InstanceOfSpecification : public DefaultSpecification
{
  public:
    InstanceOfSpecification(const Component *component);
    InstanceOfSpecification(const InstanceOfSpecification &copy);

    InstanceOfSpecification &operator=(const InstanceOfSpecification &right);

    bool isSatisfiedBy(const Base *candidate) const;

  private:
    const Component *component;

    friend InstanceOfSpecificationTest;

};

#endif // INSTANCEOFSPECIFICATION_HPP