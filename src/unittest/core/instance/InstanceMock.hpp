#ifndef INSTANCEMOCK_HPP
#define INSTANCEMOCK_HPP

#include <core/instance/IInstance.hpp>
#include <core/instance/InstancePort.hpp>

class InstanceMock :
    public virtual IInstance
{
  public:
    InstanceMock(const InstanceMock &copy) = delete;
    InstanceMock &operator =(const InstanceMock &copy) = delete;

    InstanceMock(bool *aDestroyed = nullptr);
    ~InstanceMock();

    const List<InstancePort> &getPorts() const override;
    Side portSide(PortType) const override;
    Side connectorSide(PortType) const override;
    PaperUnit getWidth() const override;
    PaperUnit getHeight() const override;

    void accept(Visitor &);
    void accept(ConstVisitor &) const;

  private:
    bool * const destroyed{nullptr};
    List<InstancePort> ports{};

};

#endif // INSTANCEMOCK_HPP
