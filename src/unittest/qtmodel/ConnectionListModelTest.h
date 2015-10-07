// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef CONNECTIONLISTMODELTEST_H
#define CONNECTIONLISTMODELTEST_H

#include <qtmodel/ConnectionListModel.hpp>
#include <core/implementation/CompositionFactory.hpp>

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class ConnectionListModelTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( ConnectionListModelTest );

    CPPUNIT_TEST(inherits_QAbstractListModel);
    CPPUNIT_TEST(has_four_columns);
    CPPUNIT_TEST(column_header_are_srcInst_srcPort_dstInst_dstPort);
    CPPUNIT_TEST(rowCount_matches_number_of_connections);
    CPPUNIT_TEST(data_returns_correct_port_names);
    CPPUNIT_TEST(data_returns_self_for_CompositionInstance);
    CPPUNIT_TEST(data_returns_name_of_instance);

    CPPUNIT_TEST(reacts_on_added_connections);
    CPPUNIT_TEST(reacts_on_removed_connections);

    CPPUNIT_TEST_SUITE_END();

  public:
    void setUp();
    void tearDown();

    void inherits_QAbstractListModel();
    void has_four_columns();
    void column_header_are_srcInst_srcPort_dstInst_dstPort();
    void rowCount_matches_number_of_connections();
    void data_returns_correct_port_names();
    void data_returns_self_for_CompositionInstance();
    void data_returns_name_of_instance();

    void reacts_on_added_connections();
    void reacts_on_removed_connections();

    //TODO notify about canged values

  private:
    Composition *composition = nullptr;
    ConnectionListModel *testee = nullptr;

};

CPPUNIT_TEST_SUITE_REGISTRATION( ConnectionListModelTest );


#endif // CONNECTIONLISTMODELTEST_H
