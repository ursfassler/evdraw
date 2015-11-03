// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef INSTANCETEST_HPP
#define INSTANCETEST_HPP

#include <core/component/Component.hpp>
#include <core/instance/Instance.hpp>

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class InstanceTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( InstanceTest );

    CPPUNIT_TEST(produce);
    CPPUNIT_TEST(setPosition);
    CPPUNIT_TEST(updatePositionOnIndexChange);
    CPPUNIT_TEST(has_position);
    CPPUNIT_TEST(inheritsBase);

    CPPUNIT_TEST(getPortWithExisting);
    CPPUNIT_TEST(getPortForNonExistingThrowsError);

    CPPUNIT_TEST(addPortWhenComponentPortIsAdded);
    CPPUNIT_TEST(deletePortWhenComponentPortIsDeleted);
    CPPUNIT_TEST(deletePortWhenComponentHasPortsWithSameName);

    CPPUNIT_TEST(setName);

    CPPUNIT_TEST(updatePortPositionsOnPortDelete);

    CPPUNIT_TEST(connector_side_of_slot_is_left);
    CPPUNIT_TEST(connector_side_of_signal_is_right);

    CPPUNIT_TEST(dimension_is_not_zero);
    CPPUNIT_TEST(height_depends_on_ports);

    CPPUNIT_TEST_SUITE_END();

  public:
    void setUp();
    void tearDown();

    void produce();
    void setPosition();
    void updatePositionOnIndexChange();
    void has_position();
    void inheritsBase();

    void getPortWithExisting();
    void getPortForNonExistingThrowsError();

    void addPortWhenComponentPortIsAdded();
    void deletePortWhenComponentPortIsDeleted();
    void deletePortWhenComponentHasPortsWithSameName();

    void setName();

    void updatePortPositionsOnPortDelete();

    void connector_side_of_slot_is_left();
    void connector_side_of_signal_is_right();

    void dimension_is_not_zero();
    void height_depends_on_ports();

  private:
    Component *component = nullptr;
    Instance *instance = nullptr;

};

CPPUNIT_TEST_SUITE_REGISTRATION( InstanceTest );

#endif // INSTANCETEST_HPP
