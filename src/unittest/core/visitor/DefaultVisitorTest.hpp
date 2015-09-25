// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef DEFAULTVISITORTEST_HPP
#define DEFAULTVISITORTEST_HPP

#include "unittest/testtypes.hpp"
#include "../implementation/CompositionInstanceMock.hpp"

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <core/component/Library.hpp>
#include <core/component/Component.hpp>
#include <core/component/ComponentPort.hpp>
#include <core/instance/Instance.hpp>
#include <core/instance/InstancePort.hpp>
#include <core/implementation/Composition.hpp>
#include <core/connection/Connection.hpp>

class DefaultVisitorTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( DefaultVisitorTest );

    CPPUNIT_TEST(inheritsVisitor);

    CPPUNIT_TEST(componentPortVisitsOnlyComponentPort);
    CPPUNIT_TEST(instancePortVisitsOnlyInstancePort);
    CPPUNIT_TEST(instanceVisitsPorts);
    CPPUNIT_TEST(connectionVisitsOnlyConnection);
    CPPUNIT_TEST(compositionVisitsInstance);
    CPPUNIT_TEST(compositionVisitsConnection);
    CPPUNIT_TEST(nullImplementationVisitsOnlyNullImplementation);
    CPPUNIT_TEST(componentVisitsPorts);
    CPPUNIT_TEST(componentVisitsImplementation);
    CPPUNIT_TEST(libraryVisitsComponents);

    CPPUNIT_TEST_SUITE_END();

  public:
    void inheritsVisitor();

    virtual void setUp();
    virtual void tearDown();

    void componentPortVisitsOnlyComponentPort();
    void instancePortVisitsOnlyInstancePort();
    void instanceVisitsPorts();
    void connectionVisitsOnlyConnection();
    void compositionVisitsInstance();
    void compositionVisitsConnection();
    void nullImplementationVisitsOnlyNullImplementation();
    void componentVisitsPorts();
    void componentVisitsImplementation();
    void libraryVisitsComponents();

  private:
    Library *library = nullptr;
    ComponentPort *slot = nullptr;
    ComponentPort *signal = nullptr;
    Component *componentNullImpl = nullptr;
    Composition *composition = nullptr;
    Component *componentComposition = nullptr;
    Instance *instance = nullptr;
    AbstractPort *instanceSlot = nullptr;
    AbstractPort *instanceSignal = nullptr;
    Connection *connection = nullptr;

};

CPPUNIT_TEST_SUITE_REGISTRATION( DefaultVisitorTest );

#endif // DEFAULTVISITORTEST_HPP
