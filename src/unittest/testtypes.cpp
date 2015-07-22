#include "testtypes.hpp"

std::ostream &operator <<(std::ostream &stream, const test::sl &list)
{
  for(const std::string &item : list)
  {
    stream << item << " ";
  }
  return stream;
}
