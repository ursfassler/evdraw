#ifndef CONNECTOR_HPP
#define CONNECTOR_HPP

#include "../base/Base.hpp"

#include "../types.hpp"

class Connector final : public Positionable
{
  public:
    Connector(Positionable *anchor, const Point &offset);

    void addPoint(Positionable *point);
    const std::vector<Positionable *> &getPoints() const;

    void setOffset(const Point &value);

  protected:
    void notify(const Positionable *subject);

  private:
    std::vector<Positionable*> points;

    void updateConnectionPosition() const;
    Point calcLocalConnectorOffset(size_t idx) const;
};

#endif // CONNECTOR_HPP
