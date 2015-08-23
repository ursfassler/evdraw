// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef TESTTYPES_HPP
#define TESTTYPES_HPP

#include <vector>
#include <string>
#include <ostream>

namespace test
{

  typedef std::vector<std::string> sl;

}

std::ostream &operator <<(std::ostream &stream, const test::sl &list);


#endif
