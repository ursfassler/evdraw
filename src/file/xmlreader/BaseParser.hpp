#ifndef BASEPARSER_HPP
#define BASEPARSER_HPP

#include <core/component/Library.hpp>
#include <tinyxml.h>

#include <string>


#include <exception>
#include <string>

class NoSuchAttributeException : public std::exception
{
  public:
    NoSuchAttributeException(const std::string &attributeName);
    virtual const char *what() const _GLIBCXX_USE_NOEXCEPT;

  protected:
    const std::string msg;
};

class NoSuchElementException: public std::exception
{
  public:
    virtual const char *what() const _GLIBCXX_USE_NOEXCEPT;
};

class BaseParser
{
  public:
    BaseParser(const Library &library, const TiXmlElement &element);

    std::string getAttribute(const std::string &attribute) const;

    const Library &library;
    const TiXmlElement &element;
};


#endif // BASEPARSER_HPP
