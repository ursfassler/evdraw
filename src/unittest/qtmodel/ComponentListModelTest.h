// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef COMPONENTLISTMODELTEST_H
#define COMPONENTLISTMODELTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <core/component/Library.hpp>
#include <qtmodel/ComponentListModel.hpp>

class ComponentListModelTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( ComponentListModelTest );

    CPPUNIT_TEST(inherits_QAbstractListModel);
    CPPUNIT_TEST(has_two_columns);
    CPPUNIT_TEST(header_caption_is_name_and_type);
    CPPUNIT_TEST(rowCount_matches_number_of_components);

    CPPUNIT_TEST_SUITE_END();

  public:
    void setUp();
    void tearDown();

    void inherits_QAbstractListModel();
    void has_two_columns();
    void header_caption_is_name_and_type();
    void rowCount_matches_number_of_components();

  private:
    Library *library{nullptr};
    ComponentListModel *testee{nullptr};

};

CPPUNIT_TEST_SUITE_REGISTRATION( ComponentListModelTest );


#endif // COMPONENTLISTMODELTEST_H
