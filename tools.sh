#!/bin/sh

#----------CHANGE-GENERATOR-----------------------
BUILD_GENERATOR="Ninja Multi-Config"
#-------------------------------------------------
#CHANGING-STUFF-OUTSIDE-THIS-SCOPE----------------
#IS-NOT-RECOMMENDED-------------------------------

BUILD_DIRECTORY="build"

EXECUTABLE_NAME="Eon"

BUILD_CONFIG="Debug"
RUN_CONFIG="Debug"

DEFAULT_COMMAND=""
GENERATE_COMMAND="generate"
BUILD_COMMAND="build"
RUN_COMMAND="run"

DEBUG_PARAM="-deb"
RELEASE_PARAM="-rel"

print_usage() {
  echo "\nUsage: $0 [ generate | build -(deb/rel) | run -(deb/rel) ]"
  echo "---------------------------------------------------------------------------"
  echo "  generate  : Generate build files with CMake"
  echo "              (you may change generator in tools.sh)"
  echo "  build     : Build files with specified generator"
  echo "              (defaults to debug if not specified)"
  echo "              (falls back if generator doesn't support multi-configuration)"
  echo "  run       : Run executable binary for specified configuration"
  echo "              (defaults to debug if not specified)"
  echo "              (falls back if generator doesn't support multi-configuration)"
  echo "---------------------------------------------------------------------------\n"
  exit 1
}

if [ "$1" = "$BUILD_COMMAND" ]; then
  if [ "$2" = "$DEBUG_PARAM" ]; then
    BUILD_CONFIG="Debug"
  elif [ "$2" = "$RELEASE_PARAM" ]; then
    BUILD_CONFIG="Release"
  elif [ -z "$2" ]; then
    BUILD_CONFIG="Debug"
  else
    echo "\nUnknown build configuration. See below:"
    print_usage
  fi
fi

if [ "$1" = "$RUN_COMMAND" ]; then
  if [ "$2" = "$DEBUG_PARAM" ]; then
    RUN_CONFIG="Debug"
  elif [ "$2" = "$RELEASE_PARAM" ]; then
    RUN_CONFIG="Release"
  elif [ -z "$2" ]; then
    RUN_CONFIG="Debug"
  else
    echo "\nUnknown executable configuration. See below:"
    print_usage
  fi
fi

generate() {
  exec cmake -B "$BUILD_DIRECTORY" -G "$BUILD_GENERATOR"
}

build() {
  exec cmake --build "$BUILD_DIRECTORY" --config "$BUILD_CONFIG" --parallel $(nproc)
}

run() {
  if [ -x "$BUILD_DIRECTORY/$RUN_CONFIG/bin/$EXECUTABLE_NAME" ]; then
    exec "./$BUILD_DIRECTORY/$RUN_CONFIG/bin/$EXECUTABLE_NAME"
  elif [ -x "$BUILD_DIRECTORY/bin/$EXECUTABLE_NAME" ]; then
    exec "./$BUILD_DIRECTORY/bin/$EXECUTABLE_NAME"
  else
    echo "Executable not found, did you build it first?"
    exit 1
  fi
}

case "$1" in
  $DEFAULT_COMMAND)
    print_usage
    ;;
  $GENERATE_COMMAND)
    generate
    ;;
  $BUILD_COMMAND)
    build
    ;;
  $RUN_COMMAND)
    run
    ;;
  *)
    echo "\nInvalid parameter. See below:"
    print_usage
    ;;
esac
