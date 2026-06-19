#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="${ROOT_DIR:-/src}"
BUILD_DIR="${BUILD_DIR:-${ROOT_DIR}/build/web}"
DIST_DIR="${DIST_DIR:-${ROOT_DIR}/dist/wall-web}"
ZIP_PATH="${ZIP_PATH:-${ROOT_DIR}/dist/wall-web.zip}"

cd "${ROOT_DIR}"

if [ ! -f "${ROOT_DIR}/engine/CMakeLists.txt" ]; then
  git submodule update --init --recursive
fi

rm -rf "${BUILD_DIR}"

emcmake cmake -S "${ROOT_DIR}" -B "${BUILD_DIR}" -G Ninja \
  -DCMAKE_BUILD_TYPE=Release \
  "-DCMAKE_CXX_FLAGS=-include cstdint -D_TTF_Font=TTF_Font"

cmake --build "${BUILD_DIR}" --config Release --parallel

if [ -d "${DIST_DIR}" ]; then
  find "${DIST_DIR}" -mindepth 1 -maxdepth 1 -exec rm -rf {} +
else
  mkdir -p "${DIST_DIR}"
fi
rm -f "${ZIP_PATH}"
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

copy_required_file "${BUILD_DIR}/index.html" "${DIST_DIR}/index.html"
copy_required_file "${BUILD_DIR}/index.js" "${DIST_DIR}/index.js"
copy_required_file "${BUILD_DIR}/index.wasm" "${DIST_DIR}/index.wasm"
copy_required_file "${BUILD_DIR}/index.data" "${DIST_DIR}/index.data"

(
  cd "$(dirname "${DIST_DIR}")"
  zip -qr "$(basename "${ZIP_PATH}")" "$(basename "${DIST_DIR}")"
)

echo "Web package created:"
echo "  ${DIST_DIR}"
echo "  ${ZIP_PATH}"
