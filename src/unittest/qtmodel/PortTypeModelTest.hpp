// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef PORTTYPEMODELTEST_H
#define PORTTYPEMODELTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class PortTypeModelTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( PortTypeModelTest );

    CPPUNIT_TEST(inherits_QAbstractListModel);
    CPPUNIT_TEST(has_all_types_as_row);
    CPPUNIT_TEST(display_role_matches_name);
    CPPUNIT_TEST(edit_role_matches_list_index);

    CPPUNIT_TEST_SUITE_END();

  public:
    void inherits_QAbstractListModel();
    void has_all_types_as_row();
    void display_role_matches_name();
    void edit_role_matches_list_index();

};

CPPUNIT_TEST_SUITE_REGISTRATION( PortTypeModelTest );

#endif // PORTTYPEMODELTEST_H
