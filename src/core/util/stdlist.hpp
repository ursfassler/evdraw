// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef STDLIST_HPP
#define STDLIST_HPP

#include <vector>
#include <algorithm>

template<typename _IIter, typename _Tp>
size_t contains(_IIter first, _IIter last, const _Tp &value)
{
  return std::find(first, last, value) != last;
}


#endif // LIST_HPP
