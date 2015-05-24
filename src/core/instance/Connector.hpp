#ifndef CONNECTOR_HPP
#define CONNECTOR_HPP

#include "../connection/Connection.hpp"
#include "../connection/Endpoint.hpp"

#include "../types.hpp"

class Connector
{
  public:
    Connector(const Point &offset);

    void addPoint(PortPoint *point);
    const std::vector<PortPoint *> &getPoints() const;

    const Point &getOffset() const;
    void setOffset(const Point &value);

  private:
    Point offset;
    std::vector<PortPoint*> points;

    void updateConnectionPosition() const;
    PaperUnit calcLocalConnectorY(size_t idx) const;
};

#endif // CONNECTOR_HPP
