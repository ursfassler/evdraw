// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef COMPOSITIONTEST_HPP
#define COMPOSITIONTEST_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class CompositionTest: public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( CompositionTest );

    CPPUNIT_TEST(create);
    CPPUNIT_TEST(addInstance);
    CPPUNIT_TEST(addConnection);
    CPPUNIT_TEST(inherits_implementation);

    CPPUNIT_TEST(getInstance);

    CPPUNIT_TEST(deleteInstance);
    CPPUNIT_TEST(deleteConnection);

    CPPUNIT_TEST(deleteInstance_removes_dependant_connections);
    CPPUNIT_TEST(deleteInstancePort_removes_dependant_connections);
    CPPUNIT_TEST(delete_selfInstance_port_removes_dependant_connections);

    CPPUNIT_TEST(addConnectionUnderConstruction_notifies_observer);
    CPPUNIT_TEST(can_not_overwrite_connectionUnderConstruction);

    CPPUNIT_TEST(finishConnectionCreation);

    CPPUNIT_TEST(has_instance_with_his_parent_component);

    CPPUNIT_TEST_SUITE_END();

  public:
    void create();
    void addInstance();
    void addConnection();
    void inherits_implementation();

    void getInstance();

    void deleteInstance();
    void deleteConnection();

    void deleteInstance_removes_dependant_connections();
    void deleteInstancePort_removes_dependant_connections();
    void delete_selfInstance_port_removes_dependant_connections();

    void addConnectionUnderConstruction_notifies_observer();
    void can_not_overwrite_connectionUnderConstruction();

    void finishConnectionCreation();

    void has_instance_with_his_parent_component();

};

CPPUNIT_TEST_SUITE_REGISTRATION( CompositionTest );


#endif
