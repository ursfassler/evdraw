// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef QTLISTFACTORYTEST_H
#define QTLISTFACTORYTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class QtListFactoryTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( QtListFactoryTest );

    CPPUNIT_TEST(create_component_list);
    CPPUNIT_TEST(create_instance_list);
    CPPUNIT_TEST(create_port_list);
    CPPUNIT_TEST(create_connection_list);

    CPPUNIT_TEST_SUITE_END();

  public:
    void create_component_list();
    void create_instance_list();
    void create_port_list();
    void create_connection_list();

};

CPPUNIT_TEST_SUITE_REGISTRATION( QtListFactoryTest );

#endif
