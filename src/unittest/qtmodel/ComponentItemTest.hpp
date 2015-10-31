// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef COMPONENTITEMTEST_HPP
#define COMPONENTITEMTEST_HPP

#include "../core/component/ComponentMock.hpp"
#include "../core/implementation/ImplementationMock.hpp"

#include <qtmodel/ComponentItem.hpp>

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class ComponentItemTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( ComponentItemTest );

    CPPUNIT_TEST(inherits_INameTypeItem);

    CPPUNIT_TEST(type_is_not_editable);

    CPPUNIT_TEST(read_name);
    CPPUNIT_TEST(read_type);

    CPPUNIT_TEST(change_name);

    CPPUNIT_TEST(has_a_type_model);

    CPPUNIT_TEST_SUITE_END();

  public:
    void setUp();

    void inherits_INameTypeItem();

    void type_is_not_editable();

    void read_name();
    void read_type();

    void change_name();

    void has_a_type_model();

    //TODO notify on name change

  private:
    ImplementationMock implementation{};
    ComponentMock component{};
    ComponentItem testee{};

};

CPPUNIT_TEST_SUITE_REGISTRATION( ComponentItemTest );


#endif // COMPONENTITEMTEST_HPP
