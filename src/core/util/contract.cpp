// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "contract.hpp"


ContractError::ContractError(const std::string &aContract, const std::string &aFunction, const std::string &aFile, int aLine) :
  contract(aContract),
  function(aFunction),
  file(aFile),
  line(aLine)
{
}

const char *ContractError::what() const _GLIBCXX_USE_NOEXCEPT
{
  msg = file + ":" + std::to_string(line) + ": " + contractName() + " does not hold: " + contract + " (" + function + ")";
  return msg.c_str();
}



PostconditionError::PostconditionError(const std::string &aContract, const std::string &aFunction, const std::string &aFile, int aLine) :
  ContractError(aContract, aFunction, aFile, aLine)
{
}

const std::string PostconditionError::contractName() const
{
  return "postcondition";
}



PreconditionError::PreconditionError(const std::string &aContract, const std::string &aFunction, const std::string &aFile, int aLine) :
  ContractError(aContract, aFunction, aFile, aLine)
{
}

const std::string PreconditionError::contractName() const
{
  return "precondition";
}



InvariantError::InvariantError(const std::string &aContract, const std::string &aFunction, const std::string &aFile, int aLine) :
  ContractError(aContract, aFunction, aFile, aLine)
{
}

const std::string InvariantError::contractName() const
{
  return "invariant";
}

