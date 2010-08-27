TEMPLATE = lib
CONFIG += debug
INCLUDEPATH += $(ALIVE_HOME)/include
INCLUDEPATH +=  $(VJ_BASE_DIR)/include/gmtl-0.6.0 \
LIBS += -L$(ALIVE_HOME)/lib -lalive
HEADERS = src/WandDirectionDisplacement.h
SOURCES = src/WandDirectionDisplacement.cpp
DEPENDPATH = src
OBJECTS_DIR = build
DESTDIR = lib
target.path = $${PREFIX}/lib
headers.files = $$HEADERS
headers.path = $${PREFIX}/include/alive/interaction
INSTALLS = target headers 

