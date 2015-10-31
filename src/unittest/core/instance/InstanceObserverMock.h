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

    void widthChanged() override;
    uint changedWidth = 0;

    void heightChanged() override;
    uint changedHeight = 0;

    void nameChanged(IInstance *instance) override;
    std::vector<IInstance *> nameChanged_instance{};

    void componentNameChanged(IInstance *instance) override;
    std::vector<IInstance *> componentNameChanged_instance{};

  private:
    bool * const destroyed = nullptr;

};

#endif // INSTANCEOBSERVERMOCK_H
