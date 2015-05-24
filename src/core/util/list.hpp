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


#endif // LIST_HPP
