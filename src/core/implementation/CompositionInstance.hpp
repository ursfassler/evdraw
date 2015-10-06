#ifndef COMPOSITIONINSTANCE_HPP
#define COMPOSITIONINSTANCE_HPP

#include "../component/Component.hpp"
#include "../instance/InstancePort.hpp"
#include "../instance/InstanceObserver.h"

class ICompositionInstance :
    public virtual IInstance
{
  public:
    virtual ~ICompositionInstance(){}

    virtual IComponent *getComponent() const = 0;

    virtual PaperUnit getWidth() const = 0;
    virtual void setWidth(PaperUnit value) = 0;
    virtual PaperUnit getHeight() const = 0;
    virtual void setHeight(PaperUnit value) = 0;

    virtual const std::vector<InstancePort *> &getPorts() const = 0;
};

class CompositionInstance final :
    public ICompositionInstance,
    private ComponentObserver
{
  public:
    CompositionInstance(const CompositionInstance&) = delete;
    void operator =(const CompositionInstance&) = delete;

    CompositionInstance(IComponent *component);
    ~CompositionInstance();

    IComponent *getComponent() const override final;

    PaperUnit getWidth() const override final;
    void setWidth(PaperUnit value) override final;
    PaperUnit getHeight() const override final;
    void setHeight(PaperUnit value) override final;

    const std::vector<InstancePort *> &getPorts() const override final;

    Side portSide(PortType type) const override final;
    Side connectorSide(PortType type) const override final;

    void accept(Visitor &visitor) override final;
    void accept(ConstVisitor &visitor) const override final;

  private:
    IComponent * const component;
    PaperUnit width = 0;
    PaperUnit height = 0;
    std::vector<InstancePort *> ports{};

    void portAdded(ComponentPort *port) override;
    void portDeleted(ComponentPort *port) override;
    void nameChanged(const std::string &name) override;
};

#endif // COMPOSITIONINSTANCE_HPP
