project(GeneticAlgorithms)
add_executable(GeneticAlgorithms main.cpp)

set(TOOLCHAIN_BUILD "${CMAKE_CXX_COMPILER_ID}${CMAKE_BUILD_TYPE}")

target_compile_definitions(GeneticAlgorithms PRIVATE
    PROJECT_SOURCE_DIR="${PROJECT_SOURCE_DIR}"
)

set_target_properties(GeneticAlgorithms
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/${TOOLCHAIN_BUILD}"
)

target_include_directories(GeneticAlgorithms PRIVATE
    include
)