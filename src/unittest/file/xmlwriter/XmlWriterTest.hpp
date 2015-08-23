// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef XMLWRITERTEST_HPP
#define XMLWRITERTEST_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class XmlWriterTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( XmlWriterTest );

    CPPUNIT_TEST(emptyToXml);
    CPPUNIT_TEST(writeEmpty);

    CPPUNIT_TEST_SUITE_END();

  public:
    void emptyToXml();
    void writeEmpty();

};

CPPUNIT_TEST_SUITE_REGISTRATION( XmlWriterTest );

#endif // XMLWRITERTEST_HPP
