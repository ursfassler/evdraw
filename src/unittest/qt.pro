# Copyright 2015 Urs Fässler, www.bitzgi.ch
# SPDX-License-Identifier:	GPL-3.0+


CONFIG -= console
CONFIG -= app_bundle
CONFIG += warn_on

QT += testlib
QT += widgets

TARGET = testapp

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -pedantic -Weffc++ -Werror

LIBS += -lcppunit

!contains(QMAKE_COMPILER, clang) {
    CONFIG(debug, debug|release) {
        LIBS += -lgcov
        QMAKE_CXXFLAGS += --coverage
    }

    coverage.target = coverage
    coverage.commands = \
        ./testapp; \
        rm moc_*.gcda; \
        lcov --directory . --base-directory $$PWD --no-external --capture --output-file coverage.info; \
        lcov --remove coverage.info "unittest/*" -o coverage.info; \
        genhtml --title "evdraw" coverage.info -o $$PWD/../coverage/
    coverage.depends = testapp
    QMAKE_EXTRA_TARGETS += coverage
}

doc.target = doc
doc.commands = doxygen $$PWD/../Doxyfile
doc.depends =
QMAKE_EXTRA_TARGETS += doc

INCLUDEPATH += ../

SOURCES += \
    qt/qthelper.cpp \
    qt/model/ComponentItemTest.cpp \
    qt/model/ImplementationTypeModelTest.cpp \
    qt/model/InstanceItemTest.cpp \
    qt/model/PortItemTest.cpp \
    qt/model/PortTypeModelTest.cpp \
    qt/model/QtConnectionItemTest.cpp \
    qt/model/QtItemIntMock.cpp \
    qt/model/QtListFactoryTest.cpp \
    qt/model/QtListTest.cpp \
    qt/model/QtNameTypeItemTest.cpp \
    ../file/RizzlyPrint.cpp \
    main.cpp \
    ../qt/component/ComboboxItemDelegate.cpp \
    ../qt/component/ComponentEditor.cpp \
    ../qt/model/ComponentItem.cpp \
    ../qt/model/ImplementationTypeModel.cpp \
    ../qt/model/InstanceItem.cpp \
    ../qt/model/PortItem.cpp \
    ../qt/model/PortTypeModel.cpp \
    ../qt/model/QtConnectionItem.cpp \
    ../qt/model/QtListFactory.cpp

HEADERS += \
    qt/model/ComponentItemTest.hpp \
    qt/model/ImplementationTypeModelTest.hpp \
    qt/model/InstanceItemTest.hpp \
    qt/model/NameTypeItemMock.hpp \
    qt/model/PortItemTest.hpp \
    qt/model/PortTypeModelTest.hpp \
    qt/model/QtConnectionItemTest.hpp \
    qt/model/QtItemIntMock.hpp \
    qt/model/QtListFactoryTest.hpp \
    qt/model/QtListTest.hpp \
    qt/model/QtNameTypeItemTest.hpp \
    qt/qthelper.hpp \
    ../file/RizzlyPrint.hpp \
    ../qt/component/ComboboxItemDelegate.hpp \
    ../qt/component/ComponentEditor.hpp \
    ../qt/component/modelfromtype.hpp \
    ../qt/model/ComponentItem.hpp \
    ../qt/model/ImplementationTypeModel.hpp \
    ../qt/model/INameTypeItem.hpp \
    ../qt/model/InstanceItem.hpp \
    ../qt/model/IQtItem.hpp \
    ../qt/model/PortItem.hpp \
    ../qt/model/PortTypeModel.hpp \
    ../qt/model/QtConnectionItem.hpp \
    ../qt/model/QtList.hpp \
    ../qt/model/QtListFactory.hpp \
    ../qt/model/QtNameTypeItem.hpp

