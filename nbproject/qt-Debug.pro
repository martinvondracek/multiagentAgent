# This file is generated automatically. Do not edit.
# Use project properties -> Build -> Qt -> Expert -> Custom Definitions.
TEMPLATE = app
DESTDIR = dist/Debug/GNU-Linux-x86
TARGET = DP_agent
VERSION = 1.0.0
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += debug 
PKGCONFIG +=
QT = core gui widgets
SOURCES += Agent.cpp AkcnyZasah.cpp CComport.cpp CiCreate.cpp CiCreateDef.cpp CoordinationPosition.cpp Obstacle.cpp Obstacles.cpp Position.cpp Positions.cpp SocketConnector.cpp SocketUtil.cpp agentForm.cpp main.cpp
HEADERS += Agent.h AkcnyZasah.h CComport.h CiCreate.h CiCreateDef.h CoordinationPosition.h Obstacle.h Obstacles.h Position.h PositionsOfAgents.h SocketConnector.h SocketUtil.h agentForm.h
FORMS += agentForm.ui
RESOURCES +=
TRANSLATIONS +=
OBJECTS_DIR = build/Debug/GNU-Linux-x86
MOC_DIR = 
RCC_DIR = 
UI_DIR = 
QMAKE_CC = gcc
QMAKE_CXX = g++
DEFINES += 
INCLUDEPATH += 
LIBS += -lpthread  -lpthread  
equals(QT_MAJOR_VERSION, 4) {
QMAKE_CXXFLAGS += -std=c++11
}
equals(QT_MAJOR_VERSION, 5) {
CONFIG += c++11
}
