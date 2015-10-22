// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef INSTANCEOFSPECIFICATION_HPP
#define INSTANCEOFSPECIFICATION_HPP

#include "../specification//DefaultSpecification.hpp"
#include "../component/Component.hpp"
#include "../base/Base.hpp"

class InstanceOfSpecificationTest;

class InstanceOfSpecification : public DefaultSpecification
{
  public:
    InstanceOfSpecification(const IComponent *component);
    InstanceOfSpecification(const InstanceOfSpecification &copy);

    InstanceOfSpecification &operator=(const InstanceOfSpecification &right);

    bool isSatisfiedBy(const Base *candidate) const;

  private:
    const IComponent *component;

    friend InstanceOfSpecificationTest;

};

#endif // INSTANCEOFSPECIFICATION_HPP
