TEMPLATE = lib
CONFIG += debug
INCLUDEPATH += $(ALIVE_HOME)/include
INCLUDEPATH += $(VJ_BASE_DIR)/include/vrjuggler-3.1.1 \
    $(VJ_BASE_DIR)/include/gmtl-0.6.0 \
    $(VJ_BASE_DIR)/include/vpr-2.3.2 \
    $(VJ_BASE_DIR)/include/jccl-1.5.0 \
    $(VJ_BASE_DIR)/include/gadgeteer-2.1.8 \
    $(VJ_BASE_DIR)/include/cppdom-1.0.1
LIBS += -L$(ALIVE_HOME)/lib -lalive
LIBS += -L$(VJ_BASE_DIR)/lib \
    -lvrj-3_1_1 \
    -lvpr-2_3_2 \
    -lsonix-1_5_0 \
    -ljccl-1_5_0 \
    -lvrj_ogl-3_1_1 \
    -lgadget-2_1_8
DEFINES += BOOST_ALL_DYN_LINK JUGGLER_DEBUG
HEADERS = src/App.h src/Input.h src/Kernel.h
SOURCES = src/App.cpp src/Input.cpp src/Kernel.cpp
DEPENDPATH = src
OBJECTS_DIR = build
DESTDIR = lib
headers.files = $$HEADERS
headers.path = ../../include/alive/juggler
target.path = ../../lib
INSTALLS = target headers

