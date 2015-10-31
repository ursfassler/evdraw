#ifndef ICOMPONENT
#define ICOMPONENT

#include "IImplementation.hpp"
#include "ComponentObserver.hpp"

#include "../util/List.hpp"
#include "../types.hpp"

#include <string>

class IComponent:
    public VisitorClient,
    //TODO move ObserverCollection out of interface
    public ObserverCollection<ComponentObserver>
{
  public:
    virtual ~IComponent() = default;

    virtual const std::string &getName() const = 0;
    virtual void setName(const std::string &value) = 0;

    virtual const List<ComponentPort> &getPorts() const = 0;
    virtual List<ComponentPort> &getPorts() = 0;
    virtual Side portSide(PortType type) const = 0;

    virtual size_t maxPortCount() const = 0;

    virtual IImplementation *getImplementation() const = 0;

};


#endif // ICOMPONENT

