cmake_minimum_required(VERSION 3.21)

# ======== CONFIG ======== #

    set(MOD_NAME "boolkasdk-example")

    # version
    set(VERSION_MAJOR 1)
    set(VERSION_MINOR 0)
    set(VERSION_PATCH 0)

    set(VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH})

    # change this to your NDK root path
    set(NDK_ROOT "C:/Users/cafeed28/Development/Tools/android-ndk-r23")

    set(OUT_PATH "${CMAKE_SOURCE_DIR}/out")

    set(BUILD_TARGET "android") # windows / android (windows must be built with msvc)
    # cringe but how

# ======== END ======== #

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUT_PATH})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUT_PATH})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

file(GLOB_RECURSE PROJECT_SRC "src/*.cpp")

include_directories(
    "include"
    "include/boolka"
    "libraries/cocos-headers/cocos2dx"
    "libraries/cocos-headers/cocos2dx/include"
    "libraries/cocos-headers/cocos2dx/kazmath/include"
    "libraries/cocos-headers/extensions"
)

if (BUILD_TARGET STREQUAL "android")

# ======== ANDROID ======== #

    set(CMAKE_SYSTEM_NAME Android)
    set(CMAKE_SYSTEM_VERSION 21)
    set(CMAKE_ANDROID_ARCH_ABI armeabi-v7a)
    set(CMAKE_ANDROID_STL_TYPE c++_static)
    set(CMAKE_ANDROID_NDK ${NDK_ROOT})

    set(TARGET_NAME "${MOD_NAME}-android")

    project(${TARGET_NAME} VERSION ${VERSION})

    add_library(${TARGET_NAME} SHARED ${PROJECT_SRC})
    
    include_directories(
        "libraries/android/dobby"
        "libraries/android/gd.h/include"
        "libraries/android/gd.h"
        "libraries/cocos-headers/cocos2dx/platform/android"
    )

    target_link_libraries(${TARGET_NAME} "${CMAKE_SOURCE_DIR}/libraries/cocos-headers/cocos2dx/libcocos2dcpp.so")
    target_link_libraries(${TARGET_NAME} "${CMAKE_SOURCE_DIR}/libraries/android/dobby/libdobby.a")
    target_link_libraries(${TARGET_NAME} "log")

    install(TARGETS ${TARGET_NAME} LIBRARY)

# ======== END ======== #

elseif (BUILD_TARGET STREQUAL "windows")

# ======== WINDOWS ======== #

    set(TARGET_NAME "${MOD_NAME}-windows")
    project(${TARGET_NAME})

    configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/src/version.rc.in"
        "${CMAKE_CURRENT_BINARY_DIR}/version.rc"
        @ONLY
    )

    add_library(${TARGET_NAME} SHARED ${PROJECT_SRC} "${CMAKE_CURRENT_BINARY_DIR}/version.rc")

    target_compile_definitions(${TARGET_NAME} PRIVATE "WIN32")
    target_compile_definitions(${TARGET_NAME} PRIVATE "_WINDOWS")

    add_subdirectory("libraries/windows/minhook")
        
    include_directories(
        "libraries/windows/minhook/include"
        "libraries/windows/gd.h/include"
        "libraries/windows/gd.h"
        "libraries/cocos-headers/cocos2dx/platform/win32"
        "libraries/cocos-headers/cocos2dx/platform/third_party/win32"
        "libraries/cocos-headers/cocos2dx/platform/third_party/win32/OGLES"
    )

    target_link_libraries(${TARGET_NAME} "minhook")
    target_link_libraries(${TARGET_NAME} "${CMAKE_SOURCE_DIR}/libraries/cocos-headers/cocos2dx/libcocos2d.lib")
    target_link_libraries(${TARGET_NAME} "${CMAKE_SOURCE_DIR}/libraries/cocos-headers/extensions/libExtensions.lib")

# ======== END ======== #

endif()