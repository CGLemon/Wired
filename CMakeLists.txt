cmake_minimum_required(VERSION 3.15)
project(Wired)

set(Boost_MIN_VERSION "1.58.0")
set(Boost_USE_MULTITHREADED ON)
find_package(Boost 1.58.0 REQUIRED program_options filesystem)

# Set up the root.
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(CHIP_SOURCES_DIR ${SOURCE_DIR}/chip)
set(UTILS_SOURCES_DIR ${SOURCE_DIR}/utils)

set(IncludePath "${CMAKE_CURRENT_SOURCE_DIR}/src")
include_directories(${IncludePath})
include_directories(${Boost_INCLUDE_DIRS})

# Set all source file.
set(BASIC_SOURCES
    ${SOURCE_DIR}/main.cc
    ${SOURCE_DIR}/config.cc
    )

set(CHIP_SOURCES
    ${CHIP_SOURCES_DIR}/marco.cc
    ${CHIP_SOURCES_DIR}/graph.cc
    ${CHIP_SOURCES_DIR}/loader.cc
    )

set(UTILS_SOURCES
    )

# Find all required packages.
find_package(Threads REQUIRED)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED on)

set(GCC_COMPILE_FLAGS "-Wall -Wextra -ffast-math -march=native -flto")
set(GCC_DISABLED_WARNING_COMPILE_FLAGS "-Wno-ignored-attributes -Wno-maybe-uninitialized -Wno-mismatched-tags")
set(CMAKE_CXX_FLAGS "${GCC_COMPILE_FLAGS} ${GCC_DISABLED_WARNING_COMPILE_FLAGS} ${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "-g -Og ${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS_RELEASE "-g -O3 -DNDEBUG ${CMAKE_CXX_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "-flto -g")

add_executable(Wired
    ${BASIC_SOURCES}
    ${CHIP_SOURCES}
    ${UTILS_SOURCES}
    )

target_link_libraries(Wired Threads::Threads)
target_link_libraries(Wired ${BLAS_LIBRARIES})
target_link_libraries(Wired ${Boost_LIBRARIES})
