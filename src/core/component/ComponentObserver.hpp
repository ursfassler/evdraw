// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef COMPONENTOBSERVER_HPP
#define COMPONENTOBSERVER_HPP

#include <string>

class ComponentObserver
{
  public:
    virtual ~ComponentObserver() = default;

    virtual void maxPortCountChanged();
    virtual void nameChanged(const std::string &name);
};

#endif // COMPONENTOBSERVER_HPP
