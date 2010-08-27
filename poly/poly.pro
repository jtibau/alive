TEMPLATE = app
CONFIG += console debug
INCLUDEPATH += $(ALIVE_HOME)/include \
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
LIBS += -L$(ALIVE_HOME)/lib -lalive -ljuggler -lWandDirectionDeltaRotation -lWandDirectionDisplacement -lWandDirectionRay
LIBS += -L$(VJ_BASE_DIR)/lib \
	-lvrj-3_1_1 \
	-lvpr-2_3_2 \
	-lsonix-1_5_0 \
	-ljccl-1_5_0 \
	-lvrj_ogl-3_1_1 \
	-lgadget-2_1_8
DEFINES += BOOST_ALL_DYN_LINK JUGGLER_DEBUG
HEADERS += src/Scene.h src/MyInteraction.h
SOURCES += src/main.cpp src/Scene.cpp src/MyInteraction.cpp
DEPENDPATH = src
OBJECTS_DIR = build
target.path = $${PREFIX}/bin
INSTALLS = target
