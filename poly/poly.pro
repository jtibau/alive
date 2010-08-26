TEMPLATE = app
CONFIG += console debug
INCLUDEPATH += include ../alive/include \
	../juggler/include \
	../interaction/WandDirectionDeltaRotation/include \
	../interaction/WandDirectionDisplacement/include \
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
LIBS += -L../alive/lib -lalive
LIBS += -L../juggler/lib -ljuggler
LIBS += -L../interaction/WandDirectionDeltaRotation/lib -lWandDirectionDeltaRotation
LIBS += -L../interaction/WandDirectionDisplacement/lib -lWandDirectionDisplacement
LIBS += -L$(VJ_BASE_DIR)/lib \
	-lvrj-3_1_1 \
    -lvpr-2_3_2 \
    -lsonix-1_5_0 \
    -ljccl-1_5_0 \
    -lvrj_ogl-3_1_1 \
    -lgadget-2_1_8
DEFINES += BOOST_ALL_DYN_LINK JUGGLER_DEBUG
HEADERS += include/alive/poly/Scene.h include/alive/poly/MyInteraction.h
SOURCES += src/main.cpp \
    src/Scene.cpp \
    src/MyInteraction.cpp
DEPENDPATH = src
OBJECTS_DIR = build
#DESTDIR =
