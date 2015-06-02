#ifndef ABSTRACTINSTANCE_HPP
#define ABSTRACTINSTANCE_HPP

#include <string>

class AbstractInstance
{
  public:
    virtual ~AbstractInstance(){}
    virtual const std::string &getName() const = 0;
};

#endif // ABSTRACTINSTANCE_HPP
