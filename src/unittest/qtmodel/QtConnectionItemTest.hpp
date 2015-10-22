// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef QTCONNECTIONITEMTEST_H
#define QTCONNECTIONITEMTEST_H

#include <qtmodel/QtConnectionItem.hpp>
#include <core/connection/Connection.hpp>
#include <core/util/List.hpp>

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class QtConnectionItemTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( QtConnectionItemTest );

    CPPUNIT_TEST(inherits_IQtItem);

    CPPUNIT_TEST(has_four_columns);
    CPPUNIT_TEST(column_header_are_srcInst_srcPort_dstInst_dstPort);
    CPPUNIT_TEST(is_not_editable);

    CPPUNIT_TEST(data_returns_correct_port_names);
    CPPUNIT_TEST(data_returns_self_for_CompositionInstance);
    CPPUNIT_TEST(data_returns_name_of_instance);

    CPPUNIT_TEST_SUITE_END();

  public:
    void inherits_IQtItem();

    void has_four_columns();
    void column_header_are_srcInst_srcPort_dstInst_dstPort();
    void is_not_editable();

    void data_returns_correct_port_names();
    void data_returns_self_for_CompositionInstance();
    void data_returns_name_of_instance();

    //TODO notify about canged values

};

CPPUNIT_TEST_SUITE_REGISTRATION( QtConnectionItemTest );


#endif
