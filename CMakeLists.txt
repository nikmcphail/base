cmake_minimum_required(VERSION 3.20)

project(base LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

set(CPM_DOWNLOAD_VERSION 0.38.7)
set(CPM_HASH_SUM "83e5eb71b2bbb8b1f2ad38f1950287a057624e385c238f6087f94cdfc44af9c5")

if (CPM_SOURCE_CACHE)
    set(CPM_DOWNLOAD_LOCATION "${CPM_SOURCE_CACHE}/cpm/CPM_${CPM_DOWNLOAD_VERSION}.cmake")
elseif (DEFINED ENV{CPM_SOURCE_CACHE})
    set(CPM_DOWNLOAD_LOCATION "$ENV{CPM_SOURCE_CACHE}/cpm/CPM_${CPM_DOWNLOAD_VERSION}.cmake")
else ()
    set(CPM_DOWNLOAD_LOCATION "${CMAKE_BINARY_DIR}/cmake/CPM_${CPM_DOWNLOAD_VERSION}.cmake")
endif ()

get_filename_component(CPM_DOWNLOAD_LOCATION ${CPM_DOWNLOAD_LOCATION} ABSOLUTE)

if (NOT EXISTS ${CPM_DL_LOCATION})
    message(STATUS "Downloading CPM.cmake to: ${CPM_DOWNLOAD_LOCATION}")

    file(DOWNLOAD
        https://github.com/cpm-cmake/CPM.cmake/releases/download/v${CPM_DOWNLOAD_VERSION}/CPM.cmake
        ${CPM_DOWNLOAD_LOCATION} EXPECTED_HASH SHA256=${CPM_HASH_SUM}
    )
endif ()

include(${CPM_DOWNLOAD_LOCATION})

CPMAddPackage(
    NAME glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 1.0.1
)

CPMAddPackage(
    NAME safetyhook
    GIT_REPOSITORY https://github.com/cursey/safetyhook.git
    GIT_TAG main
    OPTIONS "SAFETYHOOK_FETCH_ZYDIS ON"
)

CPMAddPackage("gh:ocornut/imgui@1.92.0")
CPMAddPackage("gh:freetype/freetype#d41a855aab6d8ce131c465ce01f0f536e0fb2269")
CPMAddPackage("gh:nemtrif/utfcpp@4.0.5")

add_library(base SHARED
    main.cpp
    client/client.cpp
    client/core/console/console.cpp
    client/core/interfaces/interfaces.cpp
    client/core/hooks/hooks.cpp
    client/core/render/render.cpp
    client/core/menu/menu.cpp
    library/utils.cpp
    client/core/netvars/netvars.cpp
    client/core/offsets/offsets.cpp
    client/core/global_addresses/global_addresses.cpp
    client/core/engine_prediction/engine_prediction.cpp
)

if (imgui_ADDED)
    target_sources(base PRIVATE
        ${imgui_SOURCE_DIR}/imgui.cpp
        ${imgui_SOURCE_DIR}/imgui_draw.cpp
        ${imgui_SOURCE_DIR}/imgui_tables.cpp
        ${imgui_SOURCE_DIR}/imgui_widgets.cpp
        ${imgui_SOURCE_DIR}/misc/freetype/imgui_freetype.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_win32.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_dx9.cpp
        ${imgui_SOURCE_DIR}/imgui_demo.cpp
    )

    target_include_directories(base PUBLIC
        $<BUILD_INTERFACE:${imgui_SOURCE_DIR}>
        $<BUILD_INTERFACE:${imgui_SOURCE_DIR}/backends>)

    target_compile_definitions(base PUBLIC
        IMGUI_IMPL_WIN32_DISABLE_GAMEPAD
    )
endif ()

if (utfcpp_ADDED)
    target_include_directories(base PUBLIC ${utfcpp_SOURCE_DIR}/source)
endif()

target_include_directories(base PRIVATE /)
target_compile_features(base PUBLIC cxx_std_23)
target_compile_definitions(base PRIVATE
    GLM_FORCE_SWIZZLE
    GLM_FORCE_ALIGNED_GENTYPES
    GLM_ENABLE_EXPERIMENTAL
)

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(base PRIVATE
        NDEBUG
        NOMINMAX
        _HAS_EXCEPTIONS=0
        _ITERATOR_DEBUG_LEVEL=0
        WINVER=0x0A00
        _WIN32_WINNT=0x0A00
        JSON_NOEXCEPTION
    )

    target_compile_options(base PRIVATE
        /O2
        /fp:precise
        /Ob2
        /GR-
        /GS-
        /EHsc
        /guard:cf-
        /clang:-mfpmath=sse
        /clang:-march=haswell # Haswell minimum.
        /clang:-mtune=generic
        /clang:-fno-ident
        /clang:-fno-unwind-tables
        /clang:-fno-asynchronous-unwind-tables
        /clang:-g0
    )
elseif (CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    target_compile_definitions(base PRIVATE
        NDEBUG
        NOMINMAX
        _HAS_EXCEPTIONS=0
        _ITERATOR_DEBUG_LEVEL=0
        WINVER=0x0A00
        _WIN32_WINNT=0x0A00
        JSON_NOEXCEPTION
    )

    target_compile_options(base PRIVATE
        /O2
        /fp:precise
        /Ob2
        /GR-
        /GS-
        /EHsc
        /guard:cf-
        /clang:-mfpmath=sse
        /clang:-march=haswell # Haswell minimum.
        /clang:-mtune=generic
        /clang:-fno-ident
        /clang:-fno-unwind-tables
        /clang:-fno-asynchronous-unwind-tables
        /clang:-g
    )
elseif (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(base PRIVATE
        NOMINMAX
        DEBUG
    )

    target_compile_options(base PRIVATE
        /Od
        /fp:precise
        /Ob2
        /GR-
        /GS-
        /EHsc
        /guard:cf-
        /clang:-mfpmath=sse
        /clang:-march=haswell # Haswell minimum.
        /clang:-mtune=generic
        /clang:-fno-ident
        /clang:-fno-unwind-tables
        /clang:-fno-asynchronous-unwind-tables
        /clang:-g
    )
endif ()

target_link_libraries(base PRIVATE 
    glm::glm
    freetype
    d3d9
    safetyhook
)