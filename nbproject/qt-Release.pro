# This file is generated automatically. Do not edit.
# Use project properties -> Build -> Qt -> Expert -> Custom Definitions.
TEMPLATE = app
DESTDIR = dist/Release/GNU-Linux-x86
TARGET = DP_agent
VERSION = 1.0.0
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += release 
PKGCONFIG +=
QT = core gui widgets
SOURCES += Agent.cpp CComport.cpp CiCreate.cpp CiCreateDef.cpp Poloha.cpp PolohyAgentov.cpp Prekazka.cpp Prekazky.cpp SocketConnector.cpp SocketUtil.cpp agentForm.cpp main.cpp
HEADERS += Agent.h CComport.h CiCreate.h CiCreateDef.h Poloha.h PolohyAgentov.h Prekazka.h Prekazky.h SocketConnector.h SocketUtil.h agentForm.h
FORMS += agentForm.ui
RESOURCES +=
TRANSLATIONS +=
OBJECTS_DIR = build/Release/GNU-Linux-x86
MOC_DIR = 
RCC_DIR = 
UI_DIR = 
QMAKE_CC = gcc
QMAKE_CXX = g++
DEFINES += 
INCLUDEPATH += 
LIBS += 
