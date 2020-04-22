project(Graph)
add_executable(Graph main.cpp)

set(TOOLCHAIN_BUILD "${CMAKE_CXX_COMPILER_ID}${CMAKE_BUILD_TYPE}")

target_compile_definitions(Graph PRIVATE
    PROJECT_SOURCE_DIR="${PROJECT_SOURCE_DIR}"
)

set_target_properties(Graph
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/${TOOLCHAIN_BUILD}"
)

target_include_directories(Graph PRIVATE
    include
    ${FMT_DIR}/include
)

target_link_libraries(Graph
    fmt::fmt
)