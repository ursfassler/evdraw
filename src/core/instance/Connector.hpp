#ifndef CONNECTOR_HPP
#define CONNECTOR_HPP

#include "../connection/Connection.hpp"
#include "../connection/Endpoint.hpp"

#include "../base/Base.hpp"

#include "../types.hpp"

class Connector final : public Base
{
  public:
    Connector(Base *parent, const Point &offset);

    void addPoint(PortPoint *point);
    const std::vector<PortPoint *> &getPoints() const;

    void setOffset(const Point &value);

  private:
    std::vector<PortPoint*> points;

    void updateConnectionPosition() const;
    PaperUnit calcLocalConnectorY(size_t idx) const;
};

#endif // CONNECTOR_HPP
