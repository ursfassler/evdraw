// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "contract.hpp"


ContractError::ContractError(const std::string &aContract, const std::string &aFunction) :
  contract(aContract),
  function(aFunction)
{
}

const char *ContractError::what() const _GLIBCXX_USE_NOEXCEPT
{
  return (contractName() + " does not hold: " + contract + " (" + function + ")").c_str();
}



PostconditionError::PostconditionError(const std::string &aContract, const std::string &aFunction) :
  ContractError(aContract, aFunction)
{
}

const std::string PostconditionError::contractName() const
{
  return "postcondition";
}



PreconditionError::PreconditionError(const std::string &aContract, const std::string &aFunction) :
  ContractError(aContract, aFunction)
{
}

const std::string PreconditionError::contractName() const
{
  return "precondition";
}



InvariantError::InvariantError(const std::string &aContract, const std::string &aFunction) :
  ContractError(aContract, aFunction)
{
}

const std::string InvariantError::contractName() const
{
  return "invariant";
}

