#ifndef COMPOSITIONINSTANCE_HPP
#define COMPOSITIONINSTANCE_HPP

#include "../component/Component.hpp"
#include "../instance/InstancePort.hpp"

class ICompositionInstance
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
    public IInstance,
    public ICompositionInstance,
    private ComponentObserver
{
  public:
    CompositionInstance(const CompositionInstance&) = delete;
    void operator =(const CompositionInstance&) = delete;

    CompositionInstance(IComponent *component);
    ~CompositionInstance();

    const std::string &getName() const override;

    IComponent *getComponent() const override;

    PaperUnit getWidth() const override;
    void setWidth(PaperUnit value) override;
    PaperUnit getHeight() const override;
    void setHeight(PaperUnit value) override;

    const std::vector<InstancePort *> &getPorts() const override;

    void accept(Visitor &visitor) override;
    void accept(ConstVisitor &visitor) const override;

  private:
    IComponent * const component;
    PaperUnit width = 0;
    PaperUnit height = 0;
    std::vector<InstancePort *> ports;

    void portAdded(ComponentPort *port) override;
    void portDeleted(ComponentPort *port) override;
};

#endif // COMPOSITIONINSTANCE_HPP
