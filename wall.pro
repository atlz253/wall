TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -L/usr/local/lib -lSDL2 -lSDL2_image

INCLUDEPATH += src/event \
               src/object \
               src/units \
               src/video \
               src/wall \
               src/world

SOURCES += \
  src/event/eventSubSystem.cpp \
  src/main.cpp \
  src/object/entity.cpp \
  src/object/layer.cpp \
  src/object/rotateEntity.cpp \
  src/object/textureManager.cpp \
  src/units/base.cpp \
  src/units/knight.cpp \
  src/units/unit.cpp \
  src/video/renderer.cpp \
  src/video/window.cpp \
  src/wall/globals.cpp \
  src/wall/print.cpp \
  src/wall/wall.cpp \
  src/world/action.cpp \
  src/world/background.cpp \
  src/world/terrain.cpp

HEADERS += \
  src/event/eventSubSystem.hpp \
  src/object/entity.hpp \
  src/object/layer.hpp \
  src/object/textureManager.hpp \
  src/units/base.hpp \
  src/units/knight.hpp \
  src/units/unit.hpp \
  src/video/renderer.hpp \
  src/video/window.hpp \
  src/wall/globals.hpp \
  src/wall/print.hpp \
  src/wall/wall.hpp \
  src/world/action.hpp \
  src/world/background.hpp \
  src/world/terrain.hpp

OTHER_FILES += \
  res/Knight/noBKG_KnightAttack_strip.png \
  res/Knight/noBKG_KnightRun_strip.png \
  res/Magic-Cliffs-Environment/PNG/* \
  res/Taiga-Asset-Pack_v2_vnitti/PNG/Props.png

QMAKE_POST_LINK += cp -rf $$PWD/res $$OUT_PWD/ $$escape_expand(\\n\\t)