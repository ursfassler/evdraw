// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef TYPES_HPP
#define TYPES_HPP

#include <cstdint>
#include <ostream>
#include <vector>

typedef std::int32_t PaperUnit;

enum class Side
{
    Right,
    Left
};

std::ostream &operator<<(std::ostream &stream, const std::vector<PaperUnit> &path);
std::ostream &operator<<(std::ostream &stream, const Side &connectorSide);

#endif
