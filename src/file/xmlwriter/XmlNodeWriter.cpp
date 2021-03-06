// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "XmlNodeWriter.hpp"

#include "../../core/visitor/NullConstVisitor.hpp"

#include <core/component/Library.hpp>
#include <core/instance/Instance.hpp>
#include <core/component/Component.hpp>
#include <core/implementation/Composition.hpp>
#include <core/util/contract.hpp>
#include <core/implementation/NullImplementation.hpp>


class EndpointInstanceWriter : public NullConstVisitor
{
  public:
    EndpointInstanceWriter(TiXmlElement *aElement) :
      element{aElement}
    {
    }

    EndpointInstanceWriter(const EndpointInstanceWriter &) = delete;
    EndpointInstanceWriter operator=(const EndpointInstanceWriter &) = delete;

    void visit(const Instance &instance) override
    {
      element->SetAttribute("instance", instance.getName());
    }

    void visit(const CompositionInstance &) override
    {
    }

  private:
    TiXmlElement * const element;
};



XmlNodeWriter::XmlNodeWriter(TiXmlNode *aParent) :
  parent(aParent)
{
}

void XmlNodeWriter::visit(const ComponentPort &port)
{
  TiXmlElement *element = new TiXmlElement("port");
  parent->LinkEndChild(element);
  element->SetAttribute("type", toString(port.getType()));
  element->SetAttribute("name", port.getName());
}

void XmlNodeWriter::visit(const Component &component)
{
  TiXmlElement *element = new TiXmlElement("component");
  parent->LinkEndChild(element);
  XmlNodeWriter writer(element);

  element->SetAttribute("name", component.getName());

  for (auto *inst : component.getPorts()) {
    inst->accept(writer);
  }

  component.getImplementation()->accept(writer);
}

void XmlNodeWriter::visit(const Instance &instance)
{
  TiXmlElement *element = new TiXmlElement("instance");
  parent->LinkEndChild(element);

  element->SetAttribute("name", instance.getName());
  element->SetAttribute("component", instance.getComponent()->getName());
  element->SetAttribute("x", instance.getPosition().getAbsolutePosition().x);
  element->SetAttribute("y", instance.getPosition().getAbsolutePosition().y);
}

void XmlNodeWriter::visit(const CompositionInstance &)
{
}

void XmlNodeWriter::visit(const InstancePort &port)
{
  TiXmlElement *element = new TiXmlElement("instanceport");
  parent->LinkEndChild(element);

  EndpointInstanceWriter writer(element);

  port.getInstance()->accept(writer);
  element->SetAttribute("port", port.getName());
}

void XmlNodeWriter::visit(const Connection &connection)
{
  TiXmlElement *element = new TiXmlElement("connection");
  parent->LinkEndChild(element);
  XmlNodeWriter writer(element);

  element->SetAttribute("path", buildPath(connection.getPath()));

  connection.getStartPort()->accept(writer);
  connection.getEndPort()->accept(writer);
}

std::string XmlNodeWriter::buildPath(const std::vector<PaperUnit> &path) const
{
  std::string ret("");
  bool first = true;
  for (auto pos : path) {
    if (first) {
      first = false;
    } else {
      ret += " ";
    }
    ret += std::to_string(pos);
  }
  return ret;
}

void XmlNodeWriter::visit(const Composition &composition)
{
  TiXmlElement *element = new TiXmlElement("composition");
  ICompositionInstance *selfInst = composition.getSelfInstance();
  element->SetAttribute("width", std::to_string(selfInst->getWidth()));
  element->SetAttribute("height", std::to_string(selfInst->getHeight()));

  parent->LinkEndChild(element);
  XmlNodeWriter writer(element);

  for (auto *inst : composition.getInstances()) {
    inst->accept(writer);
  }
  for (auto *con : composition.getConnections()) {
    con->accept(writer);
  }
}

void XmlNodeWriter::visit(const NullImplementation &)
{
}

void XmlNodeWriter::visit(const Library &library)
{
  TiXmlElement *element = new TiXmlElement("evdraw");
  parent->LinkEndChild(element);
  XmlNodeWriter writer(element);

  for (auto *comp : library.getComponents()) {
    comp->accept(writer);
  }
}
