cmake_minimum_required(VERSION 4.0.2..4.0.2)

add_compile_options(
  -Wall -Wextra
)

set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "a9e1cf81-9932-4810-974b-6eccaf14e457")

project(raytracer
        VERSION 0.1.0
        LANGUAGES CXX
        DESCRIPTION "Homemade Ray Tracer")

set(BOOST_UT_DISABLE_MODULE OFF)
set(CMAKE_COLOR_DIAGNOSTICS ON)
set(CMAKE_CXX_MODULE_STD ON)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)
FetchContent_Declare(ut
  GIT_REPOSITORY https://github.com/boost-ext/ut.git
  GIT_TAG v2.3.1
  GIT_SHALLOW TRUE)
FetchContent_MakeAvailable(ut)

add_library(raytracer)
target_sources(raytracer
  PUBLIC FILE_SET raytracer_public_modules TYPE CXX_MODULES
  FILES
    src/canvas.cpp
    src/raytracer.cpp
    src/mat.cpp
    src/meta.cpp
    src/ray.cpp
    src/scalar.cpp
    src/types.cpp
    src/vec.cpp
)

foreach (file
  src/mat_tests.cpp
  src/ray_tests.cpp
  src/vec_tests.cpp
)
  cmake_path(GET file STEM target)
  string(PREPEND target raytracer_)
  add_executable(${target} ${file})
  target_compile_definitions(${target} PRIVATE UNITTEST=1)
  target_link_libraries(${target} PRIVATE raytracer Boost::ut_module)
  ut_add_custom_command_or_test(TARGET ${target} COMMAND ./${target})
endforeach()

foreach (file
  src/circle.cpp
  src/clock.cpp
  src/exe1.cpp
)
  cmake_path(GET file STEM target)
  add_executable(${target} ${file})
  target_link_libraries(${target} PRIVATE raytracer)
endforeach()
