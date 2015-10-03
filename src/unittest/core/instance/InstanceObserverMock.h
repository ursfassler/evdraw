// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef INSTANCEOBSERVERMOCK_H
#define INSTANCEOBSERVERMOCK_H

#include <core/instance/InstanceObserver.h>

class InstanceObserverMock :
    public InstanceObserver
{
  public:
    InstanceObserverMock &operator=(const InstanceObserverMock&) = delete;
    InstanceObserverMock(const InstanceObserverMock&) = delete;


    InstanceObserverMock(bool *destroyed = nullptr);
    ~InstanceObserverMock();

    void portAdded(IPort *port) override;
    std::vector<IPort*> addedPorts;

    void portDeleted(IPort *port) override;
    std::vector<IPort*> deletedPorts;

    void widthChanged() override;
    uint changedWidth = 0;

    void heightChanged() override;
    uint changedHeight = 0;

    void nameChanged(const IInstance *instance) override;
    std::vector<const IInstance *> nameChanged_instance;

    void componentNameChanged(const IInstance *instance) override;
    std::vector<const IInstance *> componentNameChanged_instance;

  private:
    bool * const destroyed;

};

#endif // INSTANCEOBSERVERMOCK_H
