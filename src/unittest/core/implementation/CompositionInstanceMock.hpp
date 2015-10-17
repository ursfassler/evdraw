#ifndef COMPOSITIONINSTANCEMOCK
#define COMPOSITIONINSTANCEMOCK

#include "../instance/InstanceMock.hpp"

#include <core/implementation/CompositionInstance.hpp>

class CompositionInstanceMock :
    public ICompositionInstance,
    public InstanceMock
{
  public:
    IComponent *getComponent() const override
    {
      return nullptr;
    }

    PaperUnit getWidth() const override
    {
      return 0;
    }

    void setWidth(PaperUnit value) override
    {
      (void)(value);
    }

    void setHeight(PaperUnit value) override
    {
      (void)(value);
    }

    PaperUnit getHeight() const override
    {
      return 0;
    }

    const List<InstancePort> &getPorts() const override
    {
      return ports;
    }
    List<InstancePort> &getPorts() override
    {
      return ports;
    }
    List<InstancePort> ports{};

    void accept(Visitor &visitor) override
    {
      visitors.push_back(&visitor);
    }
    std::vector<Visitor*> visitors{};

    void accept(ConstVisitor &) const override
    {
    }


};

#endif // COMPOSITIONINSTANCEMOCK

