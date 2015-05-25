#ifndef CONTRACT_HPP
#define CONTRACT_HPP

#include <exception>
#include <string>

class ContractError : public std::exception
{
  public:
    ContractError(const std::string &aContract, const std::string &aFunction);
    virtual const char *what() const _GLIBCXX_USE_NOEXCEPT;

  protected:
    const std::string contract;
    const std::string function;

    virtual const std::string contractName() const = 0;
};

class PreconditionError : public ContractError
{
  public:
    PreconditionError(const std::string &aContract, const std::string &aFunction);

  protected:
    const std::string contractName() const;
};

#define precondition(p) \
  do { \
    if (!(p)) { \
      throw PreconditionError(#p, __func__); \
    } \
  } while(0)



class PostconditionError : public ContractError
{
  public:
    PostconditionError(const std::string &aContract, const std::string &aFunction);

  protected:
    const std::string contractName() const;
};

#define postcondition(p) \
  do { \
    if (!(p)) { \
      throw PostconditionError(#p, __func__); \
    } \
  } while(0)



class InvariantError : public ContractError
{
  public:
    InvariantError(const std::string &aContract, const std::string &aFunction);

  protected:
    const std::string contractName() const;
};

#define invariant(p) \
  do { \
    if (!(p)) { \
      throw InvariantError(#p, __func__); \
    } \
  } while(0)

#endif // CONTRACT_HPP
