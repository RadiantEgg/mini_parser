#!/bin/bash

MODE="${1:-debug}"
ACTION="${2-run}"

if [ "$MODE" = "debug" ]; then
    BUILD_TYPE="build_debug"
    CMAKE_TYPE="Debug"
elif [ "MODE" = "release" ]; then
    BUILD_TYPE="build_release"
    CMAKE_TYPE="Release
else
    echo "Usage: $0 [debug|release] [run|gdb]
    exit 1
fi

mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"
cmake -DCMAKE_BUILD_TYPE="$CMAKE_TYPE" ..
cmake --build . --target mini_parser
cd ..

EXEC="./$BUILD_DIR/LRU"
if [ "$ACTION" = "run" ]; then
    $EXEC
elif [ "$ACTION" = "gdb" ]; then
    gdb -tui $EXEC
else
    echo "Unknown action: $ACTION"
    exit 1
fi