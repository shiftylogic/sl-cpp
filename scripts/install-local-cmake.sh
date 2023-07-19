#!/usr/bin/env bash

if [[ -z ${DL_CMAKE_VERSION} ]]; then
  DL_CMAKE_VERSION="$( cat CMAKE-VERSION )"
fi

echo "Installing CMake v${DL_CMAKE_VERSION}..."


################################################
##
## Figure out what platform we are running in
##

case "$OSTYPE" in
  darwin*)
    if [[ "$(uname -m)" == "arm64" ]]; then
      DL_CMAKE_ARCH_TAG="arm64-apple-darwin22.0"
    else
      DL_CMAKE_ARCH_TAG="x64_64-apple-darwin"
    fi
    ;;
  *)
    echo "ERROR: Unsupported platform."
    ;;
esac


################################################
##
## Attempt to acquire CMake
##

DL_CMAKE_BASE="https://github.com/Kitware/CMake/releases/download"
DL_CMAKE_RELEASE_DIR="v${DL_CMAKE_VERSION}"
DL_CMAKE_RELEASE_FILE="cmake-${DL_CMAKE_VERSION}-macos-universal.tar.gz"
DL_CMAKE_URI="${DL_CMAKE_BASE}/${DL_CMAKE_RELEASE_DIR}/${DL_CMAKE_RELEASE_FILE}"

echo "  > uri: ${DL_CMAKE_URI}"

mkdir -p .tools/cmake
curl -sL "${DL_CMAKE_URI}" | tar -zx --strip-components=1 -C .tools/cmake

echo "complete"
