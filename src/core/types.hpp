#ifndef TYPES_HPP
#define TYPES_HPP

#include <cstdint>
#include <ostream>

typedef std::int32_t PaperUnit;

enum class Side
{
    Right,
    Left
};

std::ostream &operator<<(std::ostream &stream, const Side &connectorSide);

#endif
