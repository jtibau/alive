TEMPLATE = app
QT += opengl webkit
CONFIG += console debug

#### ALICE ####
INCLUDEPATH += $(ALICE_HOME)/include
LIBS += -L$(ALICE_HOME)/lib \
  -lalice \
  -ljuggler \
  -lCombination 

#### VR Juggler 3.1.1 ####
INCLUDEPATH += \
	$(VJ_BASE_DIR)/include/vrjuggler-3.1.1 \
	$(VJ_BASE_DIR)/include/gmtl-0.6.1 \
	$(VJ_BASE_DIR)/include/vpr-2.3.2 \
	$(VJ_BASE_DIR)/include/jccl-1.5.0 \
	$(VJ_BASE_DIR)/include/gadgeteer-2.1.11 \
	$(VJ_BASE_DIR)/include/cppdom-1.0.3

LIBS += -L$(VJ_BASE_DIR)/lib \
	-lvrj-3_1_1 \
	-lvpr-2_3_2 \
	-lsonix-1_5_0 \
	-ljccl-1_5_0 \
	-lvrj_ogl-3_1_1 \
	-lgadget-2_1_11

DEFINES += BOOST_ALL_DYN_LINK JUGGLER_DEBUG

#### MOVING Qt3D ####

INCLUDEPATH += $(WORKSPACE)/include/Qt3D/
LIBS += -L$(WORKSPACE) -lQt3D

#### OpenGL and OpenSceneGraph ####

LIBS += -lGL \
	-lGLU \
	-lGLEW \
	-lglut \
	-losg \
	-losgDB \
	-losgGA \
	-losgUtil \
	-lOpenThreads

#### SOURCES AND HEADERS ####

HEADERS += src/SceneRenderer.h src/App.h \
    src/Utils.h
SOURCES += src/main.cpp src/SceneRenderer.cpp src/App.cpp

FORMS += src/ui/UserInterface.ui
HEADERS += src/ui/UserInterface.h
SOURCES += src/ui/UserInterface.cpp

OTHER_FILES += src/shaders/homography.vert src/shaders/homography.frag src/shaders/homography.txt

#### Project folder layout ####

DEPENDPATH = src
OBJECTS_DIR = build
MOC_DIR = build
DESTDIR = bin

UI_DIR = src/ui
