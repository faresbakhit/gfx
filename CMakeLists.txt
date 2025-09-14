cmake_minimum_required(VERSION 4.0.2..4.0.2)

add_compile_options(
  -Wall -Wextra
)

set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "a9e1cf81-9932-4810-974b-6eccaf14e457")

project(gfx
        VERSION 0.1.0
        LANGUAGES CXX
        DESCRIPTION "Fares' Graphics Programming Code Collection")

set(CMAKE_COLOR_DIAGNOSTICS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(BOOST_UT_DISABLE_MODULE OFF)

include(FetchContent)
FetchContent_Declare(ut
  GIT_REPOSITORY https://github.com/boost-ext/ut.git
  GIT_TAG v2.3.1
  GIT_SHALLOW TRUE)
FetchContent_MakeAvailable(ut)

add_library(gfx)
target_sources(gfx
  PUBLIC FILE_SET gfx_public_modules TYPE CXX_MODULES
  FILES
    src/canvas.cpp
    src/gfx.cpp
    src/mat.cpp
    src/scalar.cpp
    src/types.cpp
    src/vec.cpp
    src/almost_equals.cpp
)
set_target_properties(gfx PROPERTIES
  CXX_STANDARD 23
  CXX_MODULE_STD ON
  CXX_SCAN_FOR_MODULES ON
)

foreach (file
  src/mat_tests.cpp
  src/vec_tests.cpp
)
  cmake_path(GET file STEM target)
  string(PREPEND target gfx_)
  add_executable(${target} ${file})
  target_link_libraries(${target} PRIVATE gfx Boost::ut_module)
  ut_add_custom_command_or_test(TARGET ${target} COMMAND ./${target})
endforeach()

add_executable(exe1 src/exe1.cpp)
target_link_libraries(exe1 PRIVATE gfx)
set_target_properties(exe1 PROPERTIES
  CXX_STANDARD 23
  CXX_MODULE_STD ON
  CXX_SCAN_FOR_MODULES ON
)
