// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef IMPLEMENTATIONMOCK_HPP
#define IMPLEMENTATIONMOCK_HPP

#include <core/component/IImplementation.hpp>

class ImplementationMock final :
    public IImplementation
{
  public:
    ImplementationMock(const ImplementationMock&) = delete;
    ImplementationMock &operator =(const ImplementationMock&) = delete;

    ImplementationMock(bool *deleted = nullptr);
    ~ImplementationMock();

    ImplementationType type{};
    ImplementationType getType() const override;

    void accept(Visitor &visitor) override;
    void accept(ConstVisitor &visitor) const override;

  private:
    bool *deleted{nullptr};
};

#endif // IMPLEMENTATIONMOCK_HPP
