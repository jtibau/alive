TEMPLATE = lib
CONFIG += debug

#### ALIVE ####

INCLUDEPATH += $(ALIVE_HOME)/include
LIBS += -L$(ALIVE_HOME)/lib -lalive

#### VR Juggler 3.1.1 ####

INCLUDEPATH += $(VJ_BASE_DIR)/include/vrjuggler-3.1.1 \
  $(VJ_BASE_DIR)/include/gmtl-0.6.0 \
  $(VJ_BASE_DIR)/include/vpr-2.3.2 \
  $(VJ_BASE_DIR)/include/jccl-1.5.0 \
  $(VJ_BASE_DIR)/include/gadgeteer-2.1.8 \
  $(VJ_BASE_DIR)/include/cppdom-1.0.1
LIBS += -L$(VJ_BASE_DIR)/lib \
  -lvrj-3_1_1 \
  -lvpr-2_3_2 \
  -lsonix-1_5_0 \
  -ljccl-1_5_0 \
  -lvrj_ogl-3_1_1 \
  -lgadget-2_1_8
DEFINES += BOOST_ALL_DYN_LINK JUGGLER_DEBUG

#### SOURCES AND HEADERS ####

HEADERS = src/App.h src/Input.h src/Kernel.h
SOURCES = src/App.cpp src/Input.cpp src/Kernel.cpp

#### Project folder layout ####

DEPENDPATH = src
OBJECTS_DIR = build
DESTDIR = lib
target.path = $${PREFIX}/lib
headers.files = $$HEADERS
headers.path = $${PREFIX}/include/alive/juggler
INSTALLS = target headers 

