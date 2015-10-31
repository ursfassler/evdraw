// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef INSTANCEITEMTEST_HPP
#define INSTANCEITEMTEST_HPP

#include "../core/instance/ComponentInstanceMock.hpp"
#include "../core/component/ComponentMock.hpp"

#include <qtmodel/QtList.hpp>
#include <qtmodel/ComponentItem.hpp>
#include <qtmodel/InstanceItem.hpp>

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class InstanceItemTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( InstanceItemTest );

    CPPUNIT_TEST(inherits_INameTypeItem);

    CPPUNIT_TEST(type_is_not_editable);
    CPPUNIT_TEST(has_a_type_model);
    CPPUNIT_TEST(read_type);

    CPPUNIT_TEST(read_name);
    CPPUNIT_TEST(change_name);

    CPPUNIT_TEST(notify_name_change);
    CPPUNIT_TEST(notify_type_change);

    CPPUNIT_TEST_SUITE_END();

  public:
    void setUp();
    void tearDown();


    void inherits_INameTypeItem();

    void type_is_not_editable();
    void has_a_type_model();
    void read_type();

    void read_name();
    void change_name();

    void notify_name_change();
    void notify_type_change();


  private:
    ComponentInstanceMock instance{};
    List<IComponent> components{};
    QtList<IComponent> types{components, new QtNameTypeItem<IComponent>(new ComponentItem())};
    InstanceItem testee{&types};

};

CPPUNIT_TEST_SUITE_REGISTRATION( InstanceItemTest );

#endif // INSTANCEITEMTEST_HPP
