TEMPLATE = lib
CONFIG += debug
INCLUDEPATH += include $(VJ_BASE_DIR)/include/gmtl-0.6.0 
HEADERS = include/alive/App.h include/alive/Input.h include/alive/InteractionMethod.h include/alive/Kernel.h include/alive/Scene.h  
SOURCES = src/App.cpp src/Input.cpp src/InteractionMethod.cpp src/Scene.cpp
DEPENDPATH = src
OBJECTS_DIR = build
DESTDIR = lib
