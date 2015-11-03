// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef QTLISTFACTORY_H
#define QTLISTFACTORY_H

#include "QtList.hpp"

#include "../core/component/IComponent.hpp"
#include "../core/component/ComponentPort.hpp"
#include "../core/instance/IComponentInstance.hpp"
#include "../core/connection/Connection.hpp"

namespace QtListFactory
{
    QtList<IComponent> *createComponentList(List<IComponent> &model, QObject *parent = 0);
    QtList<ComponentPort> *createPortList(List<ComponentPort> &model, QObject *parent = 0);
    QtList<IComponentInstance> *createInstanceList(List<IComponentInstance> &model, QtList<IComponent> *types, QObject *parent = 0);
    QtList<Connection> *createConnectionList(List<Connection> &model, QObject *parent = 0);
}

#endif // QTLISTFACTORY_H
