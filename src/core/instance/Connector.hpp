#ifndef CONNECTOR_HPP
#define CONNECTOR_HPP

#include "../base/Position.hpp"

#include "../types.hpp"

class Connector final : public RelativePosition
{
  public:
    Connector(const Point &offset);

    void addPoint(RelativePosition *point);
    const std::vector<RelativePosition *> &getPoints() const;

    void setOffset(const Point &value);

  protected:
    void notify(const RelativePosition *subject);

  private:
    std::vector<RelativePosition*> points;

    void updateConnectionPosition() const;
    Point calcLocalConnectorOffset(size_t idx) const;
};

#endif // CONNECTOR_HPP
