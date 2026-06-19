#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="${ROOT_DIR:-/src}"
BUILD_DIR="${BUILD_DIR:-${ROOT_DIR}/build/portmaster-aarch64}"
DIST_ROOT="${DIST_ROOT:-${ROOT_DIR}/dist/wall-portmaster}"
PORT_DIR="${PORT_DIR:-${DIST_ROOT}/wall}"
ZIP_PATH="${ZIP_PATH:-${ROOT_DIR}/dist/wall-portmaster.zip}"
TOOLCHAIN_FILE="${TOOLCHAIN_FILE:-${ROOT_DIR}/cmake/aarch64-linux-gnu.cmake}"
PACKAGING_DIR="${PACKAGING_DIR:-${ROOT_DIR}/packaging/portmaster}"
ARCH="${ARCH:-aarch64}"

cd "${ROOT_DIR}"

if [ ! -f "${ROOT_DIR}/engine/CMakeLists.txt" ]; then
  git submodule update --init --recursive
fi

rm -rf "${BUILD_DIR}"

cmake -S "${ROOT_DIR}" -B "${BUILD_DIR}" -G Ninja \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_TOOLCHAIN_FILE="${TOOLCHAIN_FILE}" \
  -DCMAKE_SKIP_RPATH=TRUE \
  -DCMAKE_SHARED_LIBRARY_PREFIX="" \
  "-DCMAKE_CXX_FLAGS=-include cstdint -D_TTF_Font=TTF_Font"

cmake --build "${BUILD_DIR}" --config Release --parallel

rm -rf "${DIST_ROOT}" "${ZIP_PATH}"
mkdir -p "${PORT_DIR}/libs.${ARCH}" "${PORT_DIR}/licenses"

copy_required_file() {
  local source="$1"
  local target="$2"

  if [ ! -f "${source}" ]; then
    echo "Missing expected build artifact: ${source}" >&2
    exit 1
  fi

  cp "${source}" "${target}"
}

copy_required_file "${BUILD_DIR}/wall" "${PORT_DIR}/wall.${ARCH}"

if [ -f "${BUILD_DIR}/engine/engine.so" ]; then
  copy_required_file "${BUILD_DIR}/engine/engine.so" "${PORT_DIR}/libengine.so"
  copy_required_file "${BUILD_DIR}/engine/engine.so" "${PORT_DIR}/engine.so"
elif [ -f "${BUILD_DIR}/engine/libengine.so" ]; then
  copy_required_file "${BUILD_DIR}/engine/libengine.so" "${PORT_DIR}/libengine.so"
  copy_required_file "${BUILD_DIR}/engine/libengine.so" "${PORT_DIR}/engine.so"
else
  echo "Missing expected engine shared library in ${BUILD_DIR}/engine" >&2
  exit 1
fi

cp -a "${ROOT_DIR}/res" "${PORT_DIR}/res"

copy_optional_file() {
  local source="$1"
  local target="$2"

  if [ -f "${source}" ]; then
    cp "${source}" "${target}"
  fi
}

copy_required_file "${PACKAGING_DIR}/Wall.sh" "${DIST_ROOT}/Wall.sh"
copy_required_file "${PACKAGING_DIR}/port.json" "${DIST_ROOT}/port.json"
copy_required_file "${PACKAGING_DIR}/gameinfo.xml" "${DIST_ROOT}/gameinfo.xml"
copy_required_file "${PACKAGING_DIR}/README.md" "${DIST_ROOT}/README.md"

if [ -f "${PACKAGING_DIR}/screenshot.png" ]; then
  cp "${PACKAGING_DIR}/screenshot.png" "${DIST_ROOT}/screenshot.png"
else
  copy_required_file "${ROOT_DIR}/screenshots/1.png" "${DIST_ROOT}/screenshot.png"
fi

copy_optional_file "${ROOT_DIR}/res/Magic-Cliffs-Environment/public-license.txt" "${PORT_DIR}/licenses/magic-cliffs-public-license.txt"
copy_optional_file "${ROOT_DIR}/res/Taiga-Asset-Pack_v2_vnitti/Readme.txt" "${PORT_DIR}/licenses/taiga-asset-pack-readme.txt"
copy_optional_file "${ROOT_DIR}/res/typodermic-eula-02-2014.pdf" "${PORT_DIR}/licenses/typodermic-eula-02-2014.pdf"

declare -A COPIED_LIBS=()

is_system_library() {
  case "$1" in
    ld-linux-aarch64.so.1|libc.so.6|libdl.so.2|libm.so.6|libpthread.so.0|librt.so.1)
      return 0
      ;;
    *)
      return 1
      ;;
  esac
}

find_dependency_library() {
  local lib="$1"
  local result=""

  result="$(find \
    "${PORT_DIR}" \
    /usr/lib/aarch64-linux-gnu \
    /lib/aarch64-linux-gnu \
    /usr/aarch64-linux-gnu/lib \
    \( -type f -o -type l \) \( -name "${lib}" -o -name "${lib}.*" \) -print -quit 2>/dev/null || true)"

  if [ -n "${result}" ]; then
    printf '%s\n' "${result}"
  fi
}

copy_runtime_dependencies_for() {
  local binary="$1"
  local lib
  local source
  local destination

  while IFS= read -r lib; do
    if is_system_library "${lib}"; then
      continue
    fi

    if [ -n "${COPIED_LIBS[${lib}]:-}" ]; then
      continue
    fi

    source="$(find_dependency_library "${lib}")"
    if [ -z "${source}" ]; then
      echo "Unable to locate required ARM library: ${lib}" >&2
      exit 1
    fi

    destination="${PORT_DIR}/libs.${ARCH}/${lib}"
    if [ "$(readlink -f "${source}")" != "$(readlink -f "${destination}" 2>/dev/null || true)" ]; then
      cp "${source}" "${destination}"
    fi

    COPIED_LIBS["${lib}"]=1
    copy_runtime_dependencies_for "${destination}"
  done < <(aarch64-linux-gnu-objdump -p "${binary}" | awk '/NEEDED/ { print $2 }')
}

copy_runtime_library() {
  local lib="$1"
  local source
  local destination

  if is_system_library "${lib}"; then
    return
  fi

  source="$(find_dependency_library "${lib}")"
  if [ -z "${source}" ]; then
    echo "Unable to locate required ARM library: ${lib}" >&2
    exit 1
  fi

  destination="${PORT_DIR}/libs.${ARCH}/${lib}"
  if [ "$(readlink -f "${source}")" != "$(readlink -f "${destination}" 2>/dev/null || true)" ]; then
    cp "${source}" "${destination}"
  fi

  COPIED_LIBS["${lib}"]=1
  copy_runtime_dependencies_for "${destination}"
}

copy_runtime_dependencies_for "${PORT_DIR}/wall.${ARCH}"
copy_runtime_dependencies_for "${PORT_DIR}/libengine.so"
copy_runtime_dependencies_for "${PORT_DIR}/engine.so"
copy_runtime_library "libEGL.so.1"
copy_runtime_library "libEGL_mesa.so.0"
copy_runtime_library "libGLESv2.so.2"
copy_runtime_library "libGLdispatch.so.0"

mkdir -p "${PORT_DIR}/libs.${ARCH}/egl_vendor.d" "${PORT_DIR}/libs.${ARCH}/dri" "${PORT_DIR}/libs.${ARCH}/gbm"
copy_required_file "/usr/share/glvnd/egl_vendor.d/50_mesa.json" "${PORT_DIR}/libs.${ARCH}/egl_vendor.d/50_mesa.json"
for driver in rockchip_dri.so lima_dri.so panfrost_dri.so kms_swrast_dri.so swrast_dri.so; do
  copy_required_file "/usr/lib/aarch64-linux-gnu/dri/${driver}" "${PORT_DIR}/libs.${ARCH}/dri/${driver}"
  copy_runtime_dependencies_for "${PORT_DIR}/libs.${ARCH}/dri/${driver}"
done
copy_required_file "/usr/lib/aarch64-linux-gnu/gbm/dri_gbm.so" "${PORT_DIR}/libs.${ARCH}/gbm/dri_gbm.so"
copy_runtime_dependencies_for "${PORT_DIR}/libs.${ARCH}/gbm/dri_gbm.so"

chmod +x "${DIST_ROOT}/Wall.sh" "${PORT_DIR}/wall.${ARCH}" "${PORT_DIR}/libengine.so" "${PORT_DIR}/engine.so"

(
  cd "${DIST_ROOT}"
  zip -qr "${ZIP_PATH}" "Wall.sh" "port.json" "gameinfo.xml" "README.md" "screenshot.png" "wall"
)

echo "PortMaster package created:"
echo "  ${DIST_ROOT}"
echo "  ${ZIP_PATH}"
