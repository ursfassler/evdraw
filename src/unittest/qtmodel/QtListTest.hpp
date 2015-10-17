// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef QTLISTTEST_H
#define QTLISTTEST_H

#include "QtItemIntMock.hpp"

#include <qtmodel/QtList.hpp>
#include <core/util/List.hpp>

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class QtListTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( QtListTest );

    CPPUNIT_TEST(inherits_QAbstractListModel);

    CPPUNIT_TEST(get_rowCount_from_list);
    CPPUNIT_TEST(get_columnCount_from_item);

    CPPUNIT_TEST(get_headerData_from_item);
    CPPUNIT_TEST(get_data_from_item);

    CPPUNIT_TEST(reacts_on_added_items);
    CPPUNIT_TEST(reacts_on_removed_items);

    CPPUNIT_TEST_SUITE_END();

  public:
    void setUp();
    void tearDown();

    void inherits_QAbstractListModel();

    void get_rowCount_from_list();
    void get_columnCount_from_item();

    void get_headerData_from_item();
    void get_data_from_item();

    void reacts_on_added_items();
    void reacts_on_removed_items();

  private:
    List<int> *list = nullptr;
    QtItemIntMock *item = nullptr;
    QtList<int> *testee = nullptr;

};

CPPUNIT_TEST_SUITE_REGISTRATION( QtListTest );


#endif
