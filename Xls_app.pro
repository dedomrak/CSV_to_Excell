QT += core
QT -= gui

CONFIG += c++11

TARGET = Xls_app
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    ../CSVParser/csvparser.cpp \
    ../CSVParser/support_funcs.cpp \
    BasicExcel.cpp

HEADERS += \
    ../CSVParser/csvparser.h \
    ../CSVParser/support_funcs.h \
    BasicExcel.hpp
