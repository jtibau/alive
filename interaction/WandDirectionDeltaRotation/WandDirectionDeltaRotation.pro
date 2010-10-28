TEMPLATE = lib
CONFIG += debug

#### generic math library - taken from VR Juggler for ease of parameter passing ####

INCLUDEPATH +=  $(VJ_BASE_DIR)/include/gmtl-0.6.0 \

#### ALIVE headers and the abstract library ####

INCLUDEPATH += $(ALIVE_HOME)/include
LIBS += -L$(ALIVE_HOME)/lib -lalive

#### HEADERS AND SOURCES ####

HEADERS = src/WandDirectionDeltaRotation.h
SOURCES = src/WandDirectionDeltaRotation.cpp

#### Project folder layout ####

DEPENDPATH = src
OBJECTS_DIR = build
DESTDIR = lib
target.path = $${PREFIX}/lib
headers.files = $$HEADERS
headers.path = $${PREFIX}/include/alive/interaction
INSTALLS = target headers 

