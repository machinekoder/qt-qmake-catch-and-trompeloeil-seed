QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle
CONFIG += c++14

TEMPLATE = app

include(../3rdparty/catch/catch.pri)
include(../3rdparty/trompeloeil/trompeloeil.pri)

PROJECT_DIR = $$PWD/../app

PROJECT_SOURCES = \
    $$PROJECT_DIR/order.cpp \
    $$PROJECT_DIR/warehouse.cpp \
    $$PROJECT_DIR/viennawarehouse.cpp \
    $$PROJECT_DIR/autoorder.cpp

PROJECT_HEADERS = \
    $$PROJECT_DIR/order.h \
    $$PROJECT_DIR/warehouse.h \
    $$PROJECT_DIR/viennawarehouse.h \
    $$PROJECT_DIR/autoorder.h

INCLUDEPATH += $$PROJECT_DIR

SOURCES +=  \
    main.cpp \
    tst_apptests.cpp \
    $$PROJECT_SOURCES

HEADERS += \
    $$PROJECT_HEADERS
