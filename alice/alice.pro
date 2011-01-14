TEMPLATE = lib
CONFIG += debug

#### generic math library - taken from VR Juggler for ease of parameter passing ####

INCLUDEPATH += $(VJ_BASE_DIR)/include/gmtl-0.6.1

#### HEADERS AND SOURCES ####

HEADERS = src/App.h src/InputHandler.h src/InteractionMethod.h src/Kernel.h src/SceneRenderer.h  
SOURCES = src/App.cpp src/InputHandler.cpp src/InteractionMethod.cpp src/Kernel.cpp src/SceneRenderer.cpp

NAVH = src/interaction/Navigation
MANH = src/interaction/Manipulation
SELH = src/interaction/Selection
NAVIGATION = $${NAVH}/HeadWandRotation.h $${NAVH}/PointingTranslation.h
MANIPULATION = $${MANH}/GrabRotation.h $${MANH}/GrabTranslation.h
SELECTION = $${SELH}/HeadToWandRay.h $${SELH}/WandDirectionRay.h

### Project folder layout ####

DEPENDPATH = src
OBJECTS_DIR = build
DESTDIR = lib

target.path = $${PREFIX}/lib
headers.files = $$HEADERS
headers.path = $${PREFIX}/include/alice

navigation.files = $$NAVIGATION
navigation.path = $${PREFIX}/include/alice/interaction/Navigation

manipulation.files = $$MANIPULATION
manipulation.path = $${PREFIX}/include/alice/interaction/Manipulation

selection.files = $$SELECTION
selection.path = $${PREFIX}/include/alice/interaction/Selection

INSTALLS = target headers navigation manipulation selection

