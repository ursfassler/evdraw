#include "contract.hpp"


ContractError::ContractError(const std::string &aContract, const std::string &aFunction) :
  contract(aContract),
  function(aFunction)
{
}


PreconditionError::PreconditionError(const std::string &aContract, const std::string &aFunction) :
  ContractError(aContract, aFunction)
{
}

const char *PreconditionError::what() const _GLIBCXX_USE_NOEXCEPT
{
  return ("precondition does not hold: " + contract + " (" + function + ")").c_str();
}


InvariantError::InvariantError(const std::string &aContract, const std::string &aFunction) :
  ContractError(aContract, aFunction)
{
}

const char *InvariantError::what() const _GLIBCXX_USE_NOEXCEPT
{
  return ("invariant does not hold: " + contract + " (" + function + ")").c_str();
}
