// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef QTHELPER_HPP
#define QTHELPER_HPP

#include <QVariant>
#include <ostream>

std::ostream &operator <<(std::ostream &stream, const QVariant &value);

#endif // QTHELPER_HPP
