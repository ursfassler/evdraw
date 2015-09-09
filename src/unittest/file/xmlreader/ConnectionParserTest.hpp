// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef CONNECTIONPARSERTEST_HPP
#define CONNECTIONPARSERTEST_HPP

#include <core/types.hpp>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <file/xmlreader/ConnectionParser.hpp>
#include <core/implementation/Composition.hpp>

class ConnectionTestEnvironment : public CPPUNIT_NS::TestFixture
{
  public:
    void setUp();
    void tearDown();

  protected:
    Component *compA = nullptr;
    ComponentPort *theCompPort1 = nullptr;
    ComponentPort *theCompPort2 = nullptr;
    Instance *theInstance = nullptr;
    AbstractPort *theInstPort1 = nullptr;
    AbstractPort *theInstPort2 = nullptr;
    Composition *composition = nullptr;
    Component *compB = nullptr;
    Library *library = nullptr;
    TiXmlElement  *element = nullptr;

};

class ConnectionPortParserTest : public ConnectionTestEnvironment
{
    CPPUNIT_TEST_SUITE( ConnectionPortParserTest );

    CPPUNIT_TEST(getInstance);
    CPPUNIT_TEST(getPort);

    CPPUNIT_TEST_SUITE_END();

  public:
    void setUp();
    void tearDown();

    void getInstance();
    void getPort();

  private:
    ConnectionPortParser *parser = nullptr;
};

CPPUNIT_TEST_SUITE_REGISTRATION( ConnectionPortParserTest );


class ConnectionParserTest : public ConnectionTestEnvironment
{
    CPPUNIT_TEST_SUITE( ConnectionParserTest );

    CPPUNIT_TEST(path);
    CPPUNIT_TEST(pathNotSet);
    CPPUNIT_TEST(pathHasInvalidContent);

    CPPUNIT_TEST(startPort);
    CPPUNIT_TEST(endPort);
    CPPUNIT_TEST(startAndEndPort);
    CPPUNIT_TEST(startPortDoesNotExist);
    CPPUNIT_TEST(endPortDoesNotExist);

    CPPUNIT_TEST_SUITE_END();

  public:
    void setUp();
    void tearDown();

    void path();
    void pathNotSet();
    void pathHasInvalidContent();

    void startPort();
    void endPort();
    void startAndEndPort();
    void startPortDoesNotExist();
    void endPortDoesNotExist();

  private:
    ConnectionParser *parser = nullptr;
};

CPPUNIT_TEST_SUITE_REGISTRATION( ConnectionParserTest );

#endif
