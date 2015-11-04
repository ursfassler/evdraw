// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "qthelper.hpp"


std::ostream &operator <<(std::ostream &stream, const QVariant &value)
{
  stream << value.toString().toStdString();
  return stream;
}
