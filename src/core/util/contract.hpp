#ifndef CONTRACT_HPP
#define CONTRACT_HPP

#include <exception>
#include <string>

class ContractError : public std::exception
{
  public:
    ContractError(const std::string &aContract, const std::string &aFunction);

  protected:
    const std::string contract;
    const std::string function;
};

class PreconditionError : public ContractError
{
  public:
    PreconditionError(const std::string &aContract, const std::string &aFunction);

    virtual const char *what() const _GLIBCXX_USE_NOEXCEPT;
};

class InvariantError : public ContractError
{
  public:
    InvariantError(const std::string &aContract, const std::string &aFunction);

    virtual const char *what() const _GLIBCXX_USE_NOEXCEPT;
};

#define precondition(p) \
  do { \
    if (!(p)) { \
      throw PreconditionError(#p, __func__); \
    } \
  } while(0)

#define invariant(p) \
  do { \
    if (!(p)) { \
      throw InvariantError(#p, __func__); \
    } \
  } while(0)

#endif // CONTRACT_HPP
