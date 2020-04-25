cmake_minimum_required(VERSION 3.17)
project(Advanced_Optimization_Methods)

set(CMAKE_CXX_STANDARD 17)
set(FMT_DIR ${PROJECT_SOURCE_DIR}/external/fmt)
set(OPERATORS_DIR ${PROJECT_SOURCE_DIR}/external/Generic-Ostream-Operators)

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

include_directories(SYSTEM
    ${OPERATORS_DIR}
)

add_subdirectory(${FMT_DIR})
add_subdirectory(Graph)