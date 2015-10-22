// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef QTNAMETYPEITEMTEST_HPP
#define QTNAMETYPEITEMTEST_HPP

#include "NameTypeItemMock.hpp"

#include <qtmodel/QtNameTypeItem.hpp>

#include <QStringListModel>

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class QtNameTypeItemTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( QtNameTypeItemTest );

    CPPUNIT_TEST(inherits_IQtItem);

    CPPUNIT_TEST(has_two_columns);
    CPPUNIT_TEST(header_caption_is_name_and_type);
    CPPUNIT_TEST(may_be_editable);

    CPPUNIT_TEST(get_display_data);
    CPPUNIT_TEST(get_edit_data);

    CPPUNIT_TEST(need_string_for_new_name);
    CPPUNIT_TEST(change_name);

    CPPUNIT_TEST(need_number_for_new_type);
    CPPUNIT_TEST(change_type);

    CPPUNIT_TEST_SUITE_END();

  public:
    void setUp();
    void tearDown();

    void inherits_IQtItem();

    void has_two_columns();
    void header_caption_is_name_and_type();
    void may_be_editable();

    void get_display_data();
    void get_edit_data();

    void need_string_for_new_name();
    void change_name();

    void need_number_for_new_type();
    void change_type();

    //TODO notify about canged values

  private:
    QStringListModel *typeModel = nullptr;
    NameTypeItemMock<int> *item = nullptr;
    QtNameTypeItem<int> *testee = nullptr;

};

CPPUNIT_TEST_SUITE_REGISTRATION( QtNameTypeItemTest );

#endif // QTNAMETYPEITEMTEST_HPP
