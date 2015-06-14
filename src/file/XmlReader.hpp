#ifndef XMLREADER_HPP
#define XMLREADER_HPP

#include "../core/component/Library.hpp"
#include "../core/util/contract.hpp"
#include <core/implementation/Composition.hpp>

#include <tinyxml.h>
#include <map>
#include <functional>
#include <vector>

#include "BaseParser.hpp"

class Loader final
{
  public:
    Loader();

    void nullEnter(const TiXmlElement &);
    void nullExit();

    void libraryEnter(const TiXmlElement &element);
    void libraryExit();
    void componentEnter(const TiXmlElement &element);
    void componentExit();
    void slotEnter(const TiXmlElement &element);
    void signalEnter(const TiXmlElement &element);
    void compositionEnter(const TiXmlElement &element);
    void compositionExit();
    void instanceEnter(const TiXmlElement &element);
    void connectionEnter(const TiXmlElement &element);

    Library *getLibrary() const;

  private:
    Library *lib = nullptr;
    Component *component = nullptr;
    Composition *composition = nullptr;

    ComponentPort *loadPort(const TiXmlElement &element) const;
    std::string getAttribute(const TiXmlElement &element, const std::string &attribute) const;

};

class XmlVisitor : public TiXmlVisitor
{
  public:
    XmlVisitor(Loader *loader);

    XmlVisitor(const XmlVisitor &) = delete;
    XmlVisitor operator=(const XmlVisitor &) = delete;

    virtual bool VisitEnter(const TiXmlElement &element, const TiXmlAttribute *);
    virtual bool VisitExit(const TiXmlElement &element);

  private:
    Loader * const loader;

    typedef void (Loader::*LoaderEnter)(const TiXmlElement &element);
    typedef void (Loader::*LoaderExit)();

    class Handler final
    {
      public:
        Handler()
        {
        }

        Handler(LoaderEnter aEnter, LoaderExit aExit) :
          enter(aEnter),
          exit(aExit)
        {
          invariant(enter != nullptr);
          invariant(exit != nullptr);
        }

        LoaderEnter enter = nullptr;
        LoaderExit exit = nullptr;
    };

    const std::map<std::string, Handler> elementHandler;
    std::map<std::string, Handler> getLoader();

    const Handler *getHandler(const std::string &name) const;
    void callEnter(LoaderEnter enter, const TiXmlElement &element);
    void callExit(LoaderExit exit);
};

class XmlReader
{
  public:
    static Library *parse(const std::string &data);
    static Library *loadFile(const std::string &filename);
};

#endif // XMLREADER_HPP
