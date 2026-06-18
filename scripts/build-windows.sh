#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="${ROOT_DIR:-/src}"
BUILD_DIR="${BUILD_DIR:-${ROOT_DIR}/build/windows-x64}"
DIST_DIR="${DIST_DIR:-${ROOT_DIR}/dist/wall-windows-x64}"
ZIP_PATH="${ZIP_PATH:-${ROOT_DIR}/dist/wall-windows-x64.zip}"
TRIPLET="${VCPKG_DEFAULT_TRIPLET:-x64-mingw-dynamic}"
VCPKG_ROOT="${VCPKG_ROOT:-/opt/vcpkg}"
VCPKG_INSTALLED="${VCPKG_ROOT}/installed/${TRIPLET}"
TOOLCHAIN_FILE="${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
CHAINLOAD_TOOLCHAIN_FILE="${CHAINLOAD_TOOLCHAIN_FILE:-/opt/toolchains/mingw-w64-x64.cmake}"

cd "${ROOT_DIR}"

if [ ! -f "${ROOT_DIR}/engine/CMakeLists.txt" ]; then
  git submodule update --init --recursive
fi

rm -rf "${BUILD_DIR}"

cmake -S "${ROOT_DIR}" -B "${BUILD_DIR}" -G Ninja \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_TOOLCHAIN_FILE="${TOOLCHAIN_FILE}" \
  -DVCPKG_CHAINLOAD_TOOLCHAIN_FILE="${CHAINLOAD_TOOLCHAIN_FILE}" \
  -DVCPKG_TARGET_TRIPLET="${TRIPLET}" \
  -DCMAKE_SHARED_LIBRARY_PREFIX="" \
  -DCMAKE_SHARED_LIBRARY_PREFIX_C="" \
  -DCMAKE_SHARED_LIBRARY_PREFIX_CXX="" \
  "-DCMAKE_CXX_FLAGS=-include cstdint -D_TTF_Font=TTF_Font" \
  -DSDL2_PATH="${VCPKG_INSTALLED}" \
  -DSDL2_IMAGE_PATH="${VCPKG_INSTALLED}" \
  -DSDL2_TTF_PATH="${VCPKG_INSTALLED}"

cmake --build "${BUILD_DIR}" --config Release --parallel

rm -rf "${DIST_DIR}" "${ZIP_PATH}"
mkdir -p "${DIST_DIR}"

copy_required_file() {
  local source="$1"
  local target="$2"

  if [ ! -f "${source}" ]; then
    echo "Missing expected build artifact: ${source}" >&2
    exit 1
  fi

  cp "${source}" "${target}"
}

copy_required_file "${BUILD_DIR}/wall.exe" "${DIST_DIR}/wall.exe"

if [ -f "${BUILD_DIR}/engine/engine.dll" ]; then
  copy_required_file "${BUILD_DIR}/engine/engine.dll" "${DIST_DIR}/engine.dll"
elif [ -f "${BUILD_DIR}/engine/libengine.dll" ]; then
  copy_required_file "${BUILD_DIR}/engine/libengine.dll" "${DIST_DIR}/libengine.dll"
else
  echo "Missing expected engine DLL in ${BUILD_DIR}/engine" >&2
  exit 1
fi

cp -a "${ROOT_DIR}/res" "${DIST_DIR}/res"

declare -A COPIED_DLLS=()

is_windows_system_dll() {
  case "${1,,}" in
    advapi32.dll|bcrypt.dll|comctl32.dll|comdlg32.dll|crypt32.dll|dwmapi.dll|gdi32.dll|imm32.dll|iphlpapi.dll|kernel32.dll|msvcrt.dll|ole32.dll|oleaut32.dll|rpcrt4.dll|secur32.dll|setupapi.dll|shell32.dll|shlwapi.dll|user32.dll|uuid.dll|version.dll|winmm.dll|ws2_32.dll)
      return 0
      ;;
    *)
      return 1
      ;;
  esac
}

find_dependency_dll() {
  local dll="$1"
  local result=""

  result="$(find \
    "${DIST_DIR}" \
    "${VCPKG_INSTALLED}/bin" \
    /usr/x86_64-w64-mingw32/bin \
    /usr/lib/gcc/x86_64-w64-mingw32 \
    -type f -iname "${dll}" -print -quit 2>/dev/null || true)"

  if [ -n "${result}" ]; then
    printf '%s\n' "${result}"
  fi
}

copy_runtime_dependencies_for() {
  local binary="$1"
  local dll
  local source
  local destination

  while IFS= read -r dll; do
    if is_windows_system_dll "${dll}"; then
      continue
    fi

    if [ -n "${COPIED_DLLS[${dll,,}]:-}" ]; then
      continue
    fi

    source="$(find_dependency_dll "${dll}")"
    if [ -z "${source}" ]; then
      echo "Unable to locate required DLL: ${dll}" >&2
      exit 1
    fi

    destination="${DIST_DIR}/$(basename "${source}")"
    if [ "$(readlink -f "${source}")" = "$(readlink -f "${destination}")" ]; then
      COPIED_DLLS["${dll,,}"]=1
      copy_runtime_dependencies_for "${destination}"
      continue
    fi

    cp "${source}" "${destination}"
    COPIED_DLLS["${dll,,}"]=1
    copy_runtime_dependencies_for "${destination}"
  done < <(x86_64-w64-mingw32-objdump -p "${binary}" | awk '/DLL Name:/ { print $3 }')
}

for binary in "${DIST_DIR}"/*.exe "${DIST_DIR}"/*.dll; do
  [ -f "${binary}" ] || continue
  copy_runtime_dependencies_for "${binary}"
done

(
  cd "$(dirname "${DIST_DIR}")"
  zip -qr "$(basename "${ZIP_PATH}")" "$(basename "${DIST_DIR}")"
)

echo "Windows portable build created:"
echo "  ${DIST_DIR}"
echo "  ${ZIP_PATH}"
