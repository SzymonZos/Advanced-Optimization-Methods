cmake_minimum_required(VERSION 3.17)
project(Advanced_Optimization_Methods)

set(CMAKE_CXX_STANDARD 20)
set(FMT_DIR ${PROJECT_SOURCE_DIR}/external/fmt)
set(OPERATORS_DIR ${PROJECT_SOURCE_DIR}/external/Generic-Ostream-Operators)
set(TIMER_DIR external/Timer)
set(SPDLOG_DIR external/spdlog)

add_compile_options(
#    -Werror
    -Wall
    -Wextra
    -Wshadow # Warn if variable overshadows parent context
    -Wnon-virtual-dtor # Warn if class with virtual func has no virtual dtor
    -Wcast-align # Warn for potential performance problem casts
    -Wunused # Warn on anything being unused
    -Woverloaded-virtual # Warn if overload a virtual function
    -Wpedantic # Warn if non-standard C++ is used
    -Wconversion # Warn on type conversions that may lose data
    -Wsign-conversion # Warn on sign conversions
    -Wdouble-promotion # Warn if float is implicit promoted to double
    -Wold-style-cast # Warn if c style cast is performed
    -fconstexpr-depth=1024
)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_compile_options(
        -stdlib=libc++
    )
    add_link_options(
        -stdlib=libc++
        -lc++abi
    )
endif()

include_directories(SYSTEM
    ${OPERATORS_DIR}
    ${TIMER_DIR}
)

add_subdirectory(${SPDLOG_DIR} ${CMAKE_CURRENT_BINARY_DIR}/${SPDLOG_DIR})
add_subdirectory(${FMT_DIR} ${CMAKE_CURRENT_BINARY_DIR}/${FMT_DIR})

add_subdirectory(Graph)
add_subdirectory(GeneticAlgorithms)
