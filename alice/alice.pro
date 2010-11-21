TEMPLATE = lib
CONFIG += debug

#### generic math library - taken from VR Juggler for ease of parameter passing ####

INCLUDEPATH += $(VJ_BASE_DIR)/include/gmtl-0.6.0

#### HEADERS AND SOURCES ####

HEADERS = src/App.h src/InputHandler.h src/InteractionMethod.h src/Kernel.h src/SceneRenderer.h  
SOURCES = src/App.cpp src/InputHandler.cpp src/InteractionMethod.cpp src/Kernel.cpp src/SceneRenderer.cpp

### Project folder layout ####

DEPENDPATH = src
OBJECTS_DIR = build
DESTDIR = lib

target.path = $${PREFIX}/lib
headers.files = $$HEADERS
headers.path = $${PREFIX}/include/alice
INSTALLS = target headers 

