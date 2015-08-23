// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef XMLNODEWRITERTEST_HPP
#define XMLNODEWRITERTEST_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <file/xmlwriter/XmlNodeWriter.hpp>
#include <tinyxml.h>

class XmlNodeWriterTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( XmlNodeWriterTest );

    CPPUNIT_TEST(writeEmptyLibrary);
    CPPUNIT_TEST(writeEmptyComponent);
    CPPUNIT_TEST(writeComponentWithSlots);
    CPPUNIT_TEST(writeComponentWithSignals);
    CPPUNIT_TEST(writeComponentWithSlotsAndSignals);
    CPPUNIT_TEST(writeComponentWithSlotsAndSignalsKeepsOrder);
    CPPUNIT_TEST(writeComponentWithComposition);

    CPPUNIT_TEST(writeLibraryWithComponents);

    CPPUNIT_TEST(writeInstance);

    CPPUNIT_TEST(writeEmptyComposition);
    CPPUNIT_TEST(writeCompositionWithInstances);
    CPPUNIT_TEST(writeCompositionWithConnections);

    CPPUNIT_TEST(writeInstanceInPort);
    CPPUNIT_TEST(writeInstanceOutPort);
    CPPUNIT_TEST(writeComponentInPort);
    CPPUNIT_TEST(writeComponentOutPort);

    CPPUNIT_TEST(writeConnectionPorts);
    CPPUNIT_TEST(writeConnectionPath);

    CPPUNIT_TEST_SUITE_END();

  public:
    void setUp();
    void tearDown();

    void writeEmptyLibrary();
    void writeEmptyComponent();
    void writeComponentWithSlots();
    void writeComponentWithSignals();
    void writeComponentWithSlotsAndSignals();
    void writeComponentWithSlotsAndSignalsKeepsOrder();
    void writeComponentWithComposition();

    void writeLibraryWithComponents();

    void writeInstance();

    void writeEmptyComposition();
    void writeCompositionWithInstances();
    void writeCompositionWithConnections();

    void writeInstanceInPort();
    void writeInstanceOutPort();
    void writeComponentInPort();
    void writeComponentOutPort();

    void writeConnectionPorts();
    void writeConnectionPath();

  private:
    TiXmlElement *parent = nullptr;
    XmlNodeWriter *writer = nullptr;
    const TiXmlElement &getElement() const;
    int childrenCount() const;
    int attributeCount() const;
    std::string name() const;
    std::string attr(const std::string &name) const;
    std::string childAttr(int childIndex, const std::string &name) const;
    std::string childName(int childIndex) const;
    const TiXmlElement *getChild(int index) const;
};

CPPUNIT_TEST_SUITE_REGISTRATION( XmlNodeWriterTest );


#endif // XMLNODEWRITERTEST_HPP
