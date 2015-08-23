// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "testtypes.hpp"

std::ostream &operator <<(std::ostream &stream, const test::sl &list)
{
  for(const std::string &item : list)
  {
    stream << item << " ";
  }
  return stream;
}
