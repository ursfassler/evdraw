#ifndef ERROR_HPP
#define ERROR_HPP

#include <stdexcept>

#define unreachableCode() \
  throw std::runtime_error("reached unreachablle code");

#define notYetImplemented() \
  throw std::runtime_error("not yet implemented");

#endif // ERROR_HPP
