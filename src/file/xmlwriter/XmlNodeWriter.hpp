// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef XMLNODEWRITER_HPP
#define XMLNODEWRITER_HPP

#include <core/visitor/ConstVisitor.hpp>
#include <core/types.hpp>
#include <tinyxml.h>
#include <vector>

class XmlNodeWriter final : public ConstVisitor
{
  public:
    XmlNodeWriter(TiXmlNode *parent);

    XmlNodeWriter(const XmlNodeWriter &) = delete;
    XmlNodeWriter operator=(const XmlNodeWriter &) = delete;

    void visit(const Signal &port);
    void visit(const Slot &port);
    void visit(const Component &component);
    void visit(const Instance &instance);
    void visit(const InstancePort &port);
    void visit(const Connection &connection);
    void visit(const Composition &composition);
    void visit(const NullImplementation &nullImplementation);
    void visit(const Library &library);

  private:
    TiXmlNode * const parent;

    std::string buildPath(const std::vector<PaperUnit> &path) const;
};

#endif // XMLNODEWRITER_HPP
