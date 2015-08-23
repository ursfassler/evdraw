// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef LIST_HPP
#define LIST_HPP

#include <vector>
#include <stdexcept>
#include <algorithm>

static const size_t INVALID_INDEX = -1;

template<typename _IIter, typename _Tp>
static size_t findIndex(_IIter first, _IIter last, const _Tp &value)
{
  size_t idx = 0;
  for (_IIter itr = first; itr != last; ++itr) {
      if (*itr == value) {
          return idx;
      }
      idx++;
  }
  return INVALID_INDEX;
}

template<typename _IIter, typename _Tp>
size_t contains(_IIter first, _IIter last, const _Tp &value)
{
  size_t index = findIndex(first, last, value);
  return index != INVALID_INDEX;
}

template<typename _IIter, typename _Tp>
size_t indexOf(_IIter first, _IIter last, const _Tp &value)
{
  size_t index = findIndex(first, last, value);

  if (index == INVALID_INDEX) {
    throw std::invalid_argument("element not in list");
  }

  return index;
}

template<typename _ICont, typename _IIter, typename _Predicate>
_ICont listGet(_IIter first, _IIter last, _Predicate predicate)
{
  auto itr = std::find_if(first, last, predicate);
  if (itr != last) {
    return *itr;
  } else {
    throw std::invalid_argument("element not in list");
  }
}

#endif // LIST_HPP
