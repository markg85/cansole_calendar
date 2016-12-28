QT += core
QT -= gui

QMAKE_CXXFLAGS *= -std=c++14 -O3

TARGET = console_calendar_test
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

HEADERS += \
    internal/iteratoriterator.hpp \
    internal/iterbase.hpp \
    range.hpp \
    chunked.hpp \
    zip.hpp \
    accumulate.hpp
