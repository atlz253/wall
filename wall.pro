TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -L/usr/local/lib -lSDL2 -lSDL2_image -lSDL2_ttf

INCLUDEPATH += src/event \
               src/object \
               src/units \
               src/video \
               src/wall \
               src/world

SOURCES += \
  src/event/eventSubSystem.cpp \
  src/main.cpp \
  src/object/button.cpp \
  src/object/entity.cpp \
  src/object/font.cpp \
  src/object/input.cpp \
  src/object/layer.cpp \
  src/object/rotateEntity.cpp \
  src/object/text.cpp \
  src/object/textureManager.cpp \
  src/units/base.cpp \
  src/units/knight.cpp \
  src/units/unit.cpp \
  src/video/renderer.cpp \
  src/video/window.cpp \
  src/wall/globals.cpp \
  src/wall/print.cpp \
  src/wall/random.cpp \
  src/wall/wall.cpp \
  src/world/action.cpp \
  src/world/background.cpp \
  src/world/gui.cpp \
  src/world/terrain.cpp

HEADERS += \
  src/event/eventSubSystem.hpp \
  src/object/button.hpp \
  src/object/entity.hpp \
  src/object/font.hpp \
  src/object/input.hpp \
  src/object/layer.hpp \
  src/object/text.hpp \
  src/object/textureManager.hpp \
  src/units/base.hpp \
  src/units/knight.hpp \
  src/units/unit.hpp \
  src/video/renderer.hpp \
  src/video/window.hpp \
  src/wall/globals.hpp \
  src/wall/print.hpp \
  src/wall/random.hpp \
  src/wall/wall.hpp \
  src/world/action.hpp \
  src/world/background.hpp \
  src/world/gui.hpp \
  src/world/terrain.hpp

OTHER_FILES += \
  res/joystix_monospace.ttf \
  res/typodermic-eula-02-2014.pdf \
  res/Knight/noBKG_KnightAttack_strip.png \
  res/Knight/noBKG_KnightRun_strip.png \
  res/Knight/noBKG_KnightIdle_strip.png \
  res/Knight/noBKG_KnightDeath_strip.png \
  res/Magic-Cliffs-Environment/PNG/* \
  res/Taiga-Asset-Pack_v2_vnitti/PNG/Props.png \
  res/Health-Bar-Asset-Pack-2-by-Adwit-Rahman/Health-Bar-Asset-Pack-2.2-by-Adwit-Rahman.psd \
  res/Health-Bar-Asset-Pack-2-by-Adwit-Rahman/redblue.png \
  res/Health-Bar-Asset-Pack-2-by-Adwit-Rahman/redblue2.png \

QMAKE_POST_LINK += cp -rf $$PWD/res $$OUT_PWD/ $$escape_expand(\\n\\t)
