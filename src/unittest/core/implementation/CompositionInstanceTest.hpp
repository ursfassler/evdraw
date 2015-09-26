#ifndef COMPOSITIONINSTANCETEST_HPP
#define COMPOSITIONINSTANCETEST_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class CompositionInstanceTest: public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( CompositionInstanceTest );

    CPPUNIT_TEST(create);

    CPPUNIT_TEST(can_change_width);
    CPPUNIT_TEST(can_change_height);

    CPPUNIT_TEST(create_from_component_with_ports);
    CPPUNIT_TEST(syncs_with_new_ports_in_composition);
    CPPUNIT_TEST(syncs_with_deleted_ports_in_composition);

    CPPUNIT_TEST(port_side_of_slot_is_left);
    CPPUNIT_TEST(port_side_of_signal_is_right);
    CPPUNIT_TEST(connector_side_of_slot_is_right);
    CPPUNIT_TEST(connector_side_of_signal_is_left);

    CPPUNIT_TEST_SUITE_END();

  public:
    void create();

    void can_change_width();
    void can_change_height();

    void create_from_component_with_ports();
    void syncs_with_new_ports_in_composition();
    void syncs_with_deleted_ports_in_composition();

    void port_side_of_slot_is_left();
    void port_side_of_signal_is_right();
    void connector_side_of_slot_is_right();
    void connector_side_of_signal_is_left();
};

CPPUNIT_TEST_SUITE_REGISTRATION( CompositionInstanceTest );

#endif // COMPOSITIONINSTANCETEST_HPP
