// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef PORTITEMTEST_HPP
#define PORTITEMTEST_HPP

#include <core/component/ComponentPort.hpp>

#include <qt/model/PortItem.hpp>

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class PortItemTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( PortItemTest );

    CPPUNIT_TEST(inherits_INameTypeItem);

    CPPUNIT_TEST(has_a_type_model);
    CPPUNIT_TEST(read_type);
    CPPUNIT_TEST(change_type);
    CPPUNIT_TEST(notify_type_change);

    CPPUNIT_TEST(read_name);
    CPPUNIT_TEST(change_name);
    CPPUNIT_TEST(notify_name_change);

    CPPUNIT_TEST_SUITE_END();

  public:
    void setUp();
    void tearDown();


    void inherits_INameTypeItem();

    void has_a_type_model();
    void read_type();
    void change_type();
    void notify_type_change();

    void read_name();
    void change_name();
    void notify_name_change();

  private:
    ComponentPort port{"", PortType::Signal};
    //    List<IComponent> components{};
    //    QtList<IComponent> types{components, new QtNameTypeItem<IComponent>(new ComponentItem())};
    PortItem testee{};

};

CPPUNIT_TEST_SUITE_REGISTRATION( PortItemTest );

#endif // PORTITEMTEST_HPP
