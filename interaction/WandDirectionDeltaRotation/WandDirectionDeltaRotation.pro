TEMPLATE = lib
CONFIG += debug

#### generic math library - taken from VR Juggler for ease of parameter passing ####

INCLUDEPATH +=  $(VJ_BASE_DIR)/include/gmtl-0.6.1 \

#### ALICE headers and the abstract library ####

INCLUDEPATH += $(ALICE_HOME)/include
LIBS += -L$(ALICE_HOME)/lib -lalice

#### HEADERS AND SOURCES ####

HEADERS = src/WandDirectionDeltaRotation.h
SOURCES = src/WandDirectionDeltaRotation.cpp

#### Project folder layout ####

DEPENDPATH = src
OBJECTS_DIR = build
DESTDIR = lib
target.path = $${PREFIX}/lib
headers.files = $$HEADERS
headers.path = $${PREFIX}/include/alice/interaction
INSTALLS = target headers 

