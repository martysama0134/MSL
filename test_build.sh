#!/usr/bin/env sh
set -eu

BUILD_CONFIG="${BUILD_CONFIG:-Release}"
BUILD_DIR="${BUILD_DIR:-build/dev}"
PRESET="${PRESET:-dev}"

cmake --preset "${PRESET}"
cmake --build "${BUILD_DIR}" --config "${BUILD_CONFIG}"
