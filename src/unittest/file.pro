# Copyright 2015 Urs Fässler, www.bitzgi.ch
# SPDX-License-Identifier:	GPL-3.0+


CONFIG -= console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += warn_on

QT += testlib

TARGET = testapp

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -pedantic -Weffc++ -Werror

LIBS += -ltinyxml -lcppunit

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

INCLUDEPATH += ../

SOURCES += \
    file/RizzlyPrintTest.cpp \
    file/xmlreader/BaseParserTest.cpp \
    file/xmlreader/ConnectionParserTest.cpp \
    file/xmlreader/InstanceParserTest.cpp \
    file/xmlreader/XmlReaderTest.cpp \
    file/xmlwriter/XmlNodeWriterTest.cpp \
    file/xmlwriter/XmlWriterTest.cpp \
    ../file/xmlreader/BaseParser.cpp \
    ../file/xmlreader/ConnectionParser.cpp \
    ../file/xmlreader/InstanceParser.cpp \
    ../file/xmlreader/XmlReader.cpp \
    ../file/xmlwriter/XmlNodeWriter.cpp \
    ../file/xmlwriter/XmlWriter.cpp \
    ../file/RizzlyPrint.cpp \
    main.cpp

HEADERS += \
    file/xmlreader/BaseParserTest.hpp \
    file/xmlreader/ConnectionParserTest.hpp \
    file/xmlreader/InstanceParserTest.hpp \
    file/xmlreader/XmlReaderTest.hpp \
    file/xmlwriter/XmlNodeWriterTest.hpp \
    file/xmlwriter/XmlWriterTest.hpp \
    file/RizzlyPrintTest.hpp \
    ../file/xmlreader/BaseParser.hpp \
    ../file/xmlreader/ConnectionParser.hpp \
    ../file/xmlreader/InstanceParser.hpp \
    ../file/xmlreader/XmlReader.hpp \
    ../file/xmlwriter/XmlNodeWriter.hpp \
    ../file/xmlwriter/XmlWriter.hpp \
    ../file/RizzlyPrint.hpp

