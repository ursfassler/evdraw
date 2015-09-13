// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef CONNECTORFACTORY_HPP
#define CONNECTORFACTORY_HPP

#include "Connector.hpp"

class ConnectorFactory final
{
  public:
    static void cleanup(Connector &connector);
    static void dispose(Connector *connector);
};

#endif // CONNECTORFACTORY_HPP
