TEMPLATE = app
TARGET = qtservice_server
DEPENDPATH += .
QT -= gui
CONFIG   += console qt
QT = core network

win32:CONFIG += debug_and_release build_all
win32:CONFIG -= embed_manifest_exe
unix:CONFIG += release

win32-msvc*:contains(QMAKE_TARGET.arch, x86_64):{
	QMAKE_LFLAGS *= /MACHINE:X64

	CONFIG(debug, debug|release) {
		DESTDIR = ../../../../../run/bin64_debug
		LIBS += -L../../../../../run/bin64_debug -lqtservice
		OBJECTS_DIR = ../../../../../obj/debug64/vz/qtservice_server
		MOC_DIR = ../../../../../obj/debug64/vz/qtservice_server
	} else {
		DESTDIR = ../../../../../run/bin64
		LIBS += -L../../../../../run/bin64 -lqtservice
		OBJECTS_DIR = ../../../../../obj/release64/vz/qtservice_server
		MOC_DIR = ../../../../../obj/release64/vz/qtservice_server
	}
} else {
	CONFIG(debug, debug|release) {
		DESTDIR = ../../../../../run/bin_debug
		LIBS += -L../../../../../run/bin_debug -lqtservice
		OBJECTS_DIR = ../../../../../obj/debug/vz/qtservice_server
		MOC_DIR = ../../../../../obj/debug/vz/qtservice_server
	} else {
		DESTDIR = ../../../../../run/bin
		LIBS += -L../../../../../run/bin -lqtservice
		OBJECTS_DIR = ../../../../../obj/release/vz/qtservice_server
		MOC_DIR = ../../../../../obj/release/vz/qtservice_server
	}
}

INCLUDEPATH += ../../include \
               .

SOURCES = main.cpp
