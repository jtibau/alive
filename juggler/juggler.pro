TEMPLATE = lib
CONFIG += debug
INCLUDEPATH += include ../alive/include
INCLUDEPATH += $(VJ_BASE_DIR)/include/vrjuggler-3.1.1 \
    $(VJ_BASE_DIR)/include/gmtl-0.6.0 \
    $(VJ_BASE_DIR)/include/vpr-2.3.2 \
    $(VJ_BASE_DIR)/include/jccl-1.5.0 \
    $(VJ_BASE_DIR)/include/gadgeteer-2.1.8 \
    $(VJ_BASE_DIR)/include/cppdom-1.0.1
LIBS += -L../alive/lib -lalive
LIBS += -L$(VJ_BASE_DIR)/lib \
    -lvrj-3_1_1 \
    -lvpr-2_3_2 \
    -lsonix-1_5_0 \
    -ljccl-1_5_0 \
    -lvrj_ogl-3_1_1 \
    -lgadget-2_1_8
DEFINES += BOOST_ALL_DYN_LINK JUGGLER_DEBUG
HEADERS = include/alive/juggler/App.h include/alive/juggler/Input.h include/alive/juggler/Kernel.h
SOURCES = src/App.cpp src/Input.cpp src/Kernel.cpp
DEPENDPATH = src
OBJECTS_DIR = build
DESTDIR = lib
