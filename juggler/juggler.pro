TEMPLATE = lib
CONFIG += debug

#### ALICE ####

INCLUDEPATH += $(ALICE_HOME)/include
LIBS += -L$(ALICE_HOME)/lib -lalice

#### VR Juggler 3.1.1 ####

INCLUDEPATH += $(VJ_BASE_DIR)/include/vrjuggler-3.0 \
  $(VJ_BASE_DIR)/include/gmtl-0.6.1 \
  $(VJ_BASE_DIR)/include/vpr-2.2 \
  $(VJ_BASE_DIR)/include/jccl-1.4 \
  $(VJ_BASE_DIR)/include/gadgeteer-2.0 \
  $(VJ_BASE_DIR)/include/cppdom-1.0.3
LIBS += -L$(VJ_BASE_DIR)/lib \
  -lvrj-3_0 \
  -lvpr-2_2 \
  -lsonix-1_4 \
  -ljccl-1_4 \
  -lvrj_ogl-3_0 \
  -lgadget-2_0
DEFINES += BOOST_ALL_DYN_LINK JUGGLER_DEBUG

#### SOURCES AND HEADERS ####

HEADERS = src/App.h src/InputHandler.h src/Kernel.h
SOURCES = src/App.cpp src/InputHandler.cpp src/Kernel.cpp

#### Project folder layout ####

DEPENDPATH = src
OBJECTS_DIR = build
DESTDIR = lib
target.path = $${PREFIX}/lib
headers.files = $$HEADERS
headers.path = $${PREFIX}/include/alice/juggler
INSTALLS = target headers 

