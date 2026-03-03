#!/usr/bin/env sh
set -eu

BUILD_CONFIG="${BUILD_CONFIG:-Release}"
BUILD_DIR="${BUILD_DIR:-build/dev}"

ctest --test-dir "${BUILD_DIR}" --build-config "${BUILD_CONFIG}" --output-on-failure
