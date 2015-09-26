#ifndef ERROR_HPP
#define ERROR_HPP

#include <stdexcept>
#include <string>

#define unreachableCode() \
  do { \
    throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": reached unreachable code in function " + std::string(__func__)); \
  } while(0)

#define notYetImplemented() \
  do { \
    throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": not yet implemented: " + std::string(__func__)); \
  } while(0)

#endif // ERROR_HPP
