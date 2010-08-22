TEMPLATE = app
CONFIG += console \
    debug
INCLUDEPATH += . \
    $(VJ_BASE_DIR)/include/vrjuggler-3.1.1 \
    $(VJ_BASE_DIR)/include/gmtl-0.6.0 \
    $(VJ_BASE_DIR)/include/vpr-2.3.2 \
    $(VJ_BASE_DIR)/include/jccl-1.5.0 \
    $(VJ_BASE_DIR)/include/gadgeteer-2.1.8 \
    $(VJ_BASE_DIR)/include/cppdom-1.0.1
LIBS += -lGL \
    -lGLU \
    -losg \
    -losgDB \
    -losgGA \
    -losgUtil \
    -lOpenThreads
LIBS += -L$(VJ_BASE_DIR)/lib \
    -lvrj-3_1_1 \
    -lvpr-2_3_2 \
    -lsonix-1_5_0 \
    -ljccl-1_5_0 \
    -lvrj_ogl-3_1_1 \
    -lgadget-2_1_8
DEFINES += BOOST_ALL_DYN_LINK \
    JUGGLER_DEBUG
HEADERS = alive/App.h \
    alive/Input.h \
    alive/InteractionMethod.h \
    alive/Scene.h
HEADERS += alive/juggler/App.h \
    alive/juggler/Input.h \
    alive/juggler/Kernel.h
HEADERS += alive/interaction/BasicNavigation.h
SOURCES = 
HEADERS += alive/poly/Scene.h
SOURCES = alive/poly/main.cpp \
    alive/poly/Scene.cpp
DEPENDPATH = alive/poly
DEPENDPATH += alive \
    alive/juggler \
    alive/interaction
OBJECTS_DIR = build
