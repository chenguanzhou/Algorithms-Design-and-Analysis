TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

unix{
QMAKE_CXXFLAGS += -std=c++0x
}
