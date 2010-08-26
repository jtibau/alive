TEMPLATE = lib
CONFIG += debug
INCLUDEPATH += $(VJ_BASE_DIR)/include/gmtl-0.6.0 
HEADERS = src/App.h src/Input.h src/InteractionMethod.h src/Kernel.h src/Scene.h  
SOURCES = src/App.cpp src/Input.cpp src/InteractionMethod.cpp src/Scene.cpp
DEPENDPATH = src
OBJECTS_DIR = build
DESTDIR = lib
headers.files = $$HEADERS
headers.path = ../../include/alive
target.path = ../../lib
INSTALLS = target headers