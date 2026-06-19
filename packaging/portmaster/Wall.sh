#!/bin/bash

XDG_DATA_HOME=${XDG_DATA_HOME:-$HOME/.local/share}

if [ -d "/opt/system/Tools/PortMaster/" ]; then
  controlfolder="/opt/system/Tools/PortMaster"
elif [ -d "/opt/tools/PortMaster/" ]; then
  controlfolder="/opt/tools/PortMaster"
elif [ -d "$XDG_DATA_HOME/PortMaster/" ]; then
  controlfolder="$XDG_DATA_HOME/PortMaster"
else
  controlfolder="/roms/ports/PortMaster"
fi

source "$controlfolder/control.txt"
[ -f "${controlfolder}/mod_${CFW_NAME}.txt" ] && source "${controlfolder}/mod_${CFW_NAME}.txt"

get_controls

GAMEDIR=/$directory/ports/wall
CONFDIR="$GAMEDIR/conf"

mkdir -p "$CONFDIR"
cd "$GAMEDIR" || exit 1

> "$GAMEDIR/log.txt" && exec > >(tee "$GAMEDIR/log.txt") 2>&1

export XDG_DATA_HOME="$CONFDIR"
export LD_LIBRARY_PATH="$GAMEDIR/libs.${DEVICE_ARCH}:$LD_LIBRARY_PATH"
export SDL_GAMECONTROLLERCONFIG="$sdl_controllerconfig"
export SDL_VIDEO_EGL_DRIVER="$GAMEDIR/libs.${DEVICE_ARCH}/libEGL.so.1"
export SDL_VIDEO_GL_DRIVER="$GAMEDIR/libs.${DEVICE_ARCH}/libGLESv2.so.2"
export __EGL_VENDOR_LIBRARY_FILENAMES="$GAMEDIR/libs.${DEVICE_ARCH}/egl_vendor.d/50_mesa.json"
export LIBGL_DRIVERS_PATH="$GAMEDIR/libs.${DEVICE_ARCH}/dri"
export GBM_BACKENDS_PATH="$GAMEDIR/libs.${DEVICE_ARCH}/gbm"

$GPTOKEYB "wall.${DEVICE_ARCH}" &
pm_platform_helper "$GAMEDIR/wall.${DEVICE_ARCH}"
"$GAMEDIR/wall.${DEVICE_ARCH}"

pm_finish
