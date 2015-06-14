#include "XmlReader.hpp"

#include "InstanceParser.hpp"
#include "ConnectionParser.hpp"

#include <core/instance/Instance.hpp>
#include <core/instance/InstanceFactory.hpp>
#include <core/connection/Connection.hpp>
#include <core/connection/ConnectionFactory.hpp>

#include <iostream>

Library *XmlReader::parse(const std::string &data)
{
  TiXmlDocument doc;
  doc.Parse(data.c_str());

  Loader l;
  XmlVisitor loader(&l);
  doc.Accept(&loader);

  return l.getLibrary();
}

Library *XmlReader::loadFile(const std::string &filename)
{
  TiXmlDocument doc;
  doc.LoadFile(filename);

  Loader l;
  XmlVisitor loader(&l);
  doc.Accept(&loader);

  return l.getLibrary();
}


XmlVisitor::XmlVisitor(Loader *aLoader) :
  loader(aLoader),
  elementHandler(getLoader())
{
}

std::map<std::string, XmlVisitor::Handler> XmlVisitor::getLoader()
{
  std::map<std::string, XmlVisitor::Handler> ret;

  ret["evdraw"] = Handler(&Loader::libraryEnter, &Loader::libraryExit);
  ret["component"] = Handler(&Loader::componentEnter, &Loader::componentExit);
  ret["slot"] = Handler(&Loader::slotEnter, &Loader::nullExit);
  ret["signal"] = Handler(&Loader::signalEnter, &Loader::nullExit);
  ret["composition"] = Handler(&Loader::compositionEnter, &Loader::compositionExit);
  ret["instance"] = Handler(&Loader::instanceEnter, &Loader::nullExit);
  ret["connection"] = Handler(&Loader::connectionEnter, &Loader::nullExit);
  ret["instanceport"] = Handler(&Loader::nullEnter, &Loader::nullExit);

  return ret;
}

const XmlVisitor::Handler *XmlVisitor::getHandler(const std::string &name) const
{
  std::map<std::string, Handler>::const_iterator itr = elementHandler.find(name);
  if (itr != elementHandler.end()) {
    return &itr->second;
  } else {
    throw std::runtime_error("unhandled node: " + name);
    return nullptr;
  }
}

void XmlVisitor::callEnter(LoaderEnter enter, const TiXmlElement &element)
{
  (*loader.*(enter))(element);
}

void XmlVisitor::callExit(XmlVisitor::LoaderExit exit)
{
  (*loader.*(exit))();
}

bool XmlVisitor::VisitEnter(const TiXmlElement &element, const TiXmlAttribute *)
{
  const Handler *loader = getHandler(element.Value());
  callEnter(loader->enter, element);
  return true;
}

bool XmlVisitor::VisitExit(const TiXmlElement &element)
{
  const Handler *loader = getHandler(element.Value());
  callExit(loader->exit);
  return true;
}


Loader::Loader()
{
}

void Loader::nullEnter(const TiXmlElement &)
{
}

void Loader::nullExit()
{
}

Library *Loader::getLibrary() const
{
  return lib;
}

std::string Loader::getAttribute(const TiXmlElement &element, const std::string &attribute) const
{
  std::string value = "";
  if (element.QueryStringAttribute(attribute.c_str(), &value) != TIXML_SUCCESS) {
  }
  return value;
}

void Loader::libraryEnter(const TiXmlElement &)
{
  precondition(lib == nullptr);

  lib = new Library();
}

void Loader::libraryExit()
{
  precondition(lib != nullptr);
}

void Loader::componentEnter(const TiXmlElement &element)
{
  precondition(lib != nullptr);
  precondition(component == nullptr);

  const std::string name = getAttribute(element, "name");
  component = new Component(name);
}

void Loader::componentExit()
{
  precondition(lib != nullptr);
  precondition(component != nullptr);

  lib->add(component);
  component = nullptr;
}

void Loader::slotEnter(const TiXmlElement &element)
{
  precondition(component != nullptr);

  component->addPortLeft(loadPort(element));
}

void Loader::signalEnter(const TiXmlElement &element)
{
  precondition(component != nullptr);

  component->addPortRight(loadPort(element));
}

void Loader::compositionEnter(const TiXmlElement &)
{
  precondition(composition == nullptr);

  composition = new Composition();
}

void Loader::compositionExit()
{
  precondition(component != nullptr);
  precondition(composition != nullptr);

  component->setImplementation(composition);
  composition = nullptr;
}

void Loader::instanceEnter(const TiXmlElement &element)
{
  precondition(lib != nullptr);
  precondition(composition != nullptr);

  InstanceParser parser(*lib, element);
  Instance *instance = InstanceFactory::produce(parser.component(), parser.name(), parser.position());
  composition->addInstance(instance);
}

void Loader::connectionEnter(const TiXmlElement &element)
{
  precondition(composition != nullptr);
  precondition(lib != nullptr);

  ConnectionParser parser(*lib, element, *composition);
  Connection * connection = ConnectionFactory::produce(parser.startPort(), parser.endPort(), parser.path());
  composition->addConnection(connection);
}

ComponentPort *Loader::loadPort(const TiXmlElement &element) const
{
  const std::string name = getAttribute(element, "name");
  ComponentPort *port = new ComponentPort(name);
  return port;
}



