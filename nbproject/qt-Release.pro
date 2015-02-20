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
SOURCES += CComport.cpp CiCreate.cpp CiCreateDef.cpp agentClass.cpp agentForm.cpp main.cpp polohaClass.cpp prekazkaClass.cpp socketClass.cpp socketUtilClass.cpp
HEADERS += CComport.h CiCreate.h CiCreateDef.h agentClass.h agentForm.h polohaClass.h prekazkaClass.h socketClass.h socketUtilClass.h
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
