#ifndef LIST_HPP
#define LIST_HPP

#include <vector>
#include <stdexcept>

static const size_t INVALID_INDEX = -1;

template<class T>
static size_t findIndex(const T *element, const std::vector<T *> &list)
{
  for (unsigned i = 0; i < list.size(); i++) {
    if (list[i] == element) {
      return i;
    }
  }

  return INVALID_INDEX;
}

template<class T>
size_t contains(const T *element, const std::vector<T *> &list)
{
  size_t index = findIndex(element, list);
  return index != INVALID_INDEX;
}

template<class T>
size_t indexOf(const T *element, const std::vector<T *> &list)
{
  size_t index = findIndex(element, list);

  if (index == INVALID_INDEX) {
    throw std::invalid_argument("element not in list");
  }

  return index;
}


#endif // LIST_HPP
