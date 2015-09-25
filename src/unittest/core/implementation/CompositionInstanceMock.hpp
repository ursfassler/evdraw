#ifndef COMPOSITIONINSTANCEMOCK
#define COMPOSITIONINSTANCEMOCK

#include <core/implementation/CompositionInstance.hpp>

class CompositionInstanceMock : public ICompositionInstance
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

    const std::vector<InstancePort *> &getPorts() const override
    {
      static std::vector<InstancePort *> ports;
      return ports;
    }

};

#endif // COMPOSITIONINSTANCEMOCK

