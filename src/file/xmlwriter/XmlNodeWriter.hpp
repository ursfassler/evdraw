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

    void visit(const ComponentPort &port) override final;
    void visit(const Component &component) override final;
    void visit(const Instance &instance) override final;
    void visit(const CompositionInstance &instance) override final;
    void visit(const InstancePort &port) override final;
    void visit(const Connection &connection) override final;
    void visit(const Composition &composition) override final;
    void visit(const NullImplementation &nullImplementation) override final;
    void visit(const Library &library) override final;

  private:
    TiXmlNode * const parent;

    std::string buildPath(const std::vector<PaperUnit> &path) const;
};

#endif // XMLNODEWRITER_HPP
