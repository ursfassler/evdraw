#ifndef RIZZLYPRINT_HPP
#define RIZZLYPRINT_HPP

#include "../core/sheet/Sheet.hpp"

#include <ostream>

class RizzlyPrint
{
  public:
    RizzlyPrint(std::ostream &stream);

    void print(const Sheet &sheet);
    void print(const Instance *instance);
    void print(const Connection *connection);
    void print(const AbstractPort *port);

  private:
    std::ostream &stream;
};

#endif // RIZZLYPRINT_HPP
