cmake_minimum_required(VERSION 3.10.0)
set(CMAKE_CUDA_ARCHITECTURES native)
project(CUDAGLFractal VERSION 0.1.0 LANGUAGES C CXX CUDA)

# GLAD
set(GLAD_DIR ./glad)
set(GLAD_FILES ${GLAD_DIR}/glad.h ${GLAD_DIR}/khrplatform.h ${GLAD_DIR}/glad.c)

# shaderman
set(SHADERMAN_DIR ./src/shaderman)
set(SHADERMAN_FILES ${SHADERMAN_DIR}/shaderfile.h ${SHADERMAN_DIR}/shaderfile.cpp ${SHADERMAN_DIR}/shaderman.h ${SHADERMAN_DIR}/shaderman.cpp)

# View
set(VIEW_DIR ./src/view)
set(VIEW_FILES ${VIEW_DIR}/view.h ${VIEW_DIR}/view.cpp)

# Controller
set(CONTROLLER_DIR ./src/controller)
set(CONTROLLER_FILES ${CONTROLLER_DIR}/controller.h ${CONTROLLER_DIR}/controller.cpp)

# Generator
set(GENERATOR_DIR ./src/generator)
set(GENERATOR_FILES ${GENERATOR_DIR}/generator.h ${GENERATOR_DIR}/generator.cpp ${GENERATOR_DIR}/generator.cu ${GENERATOR_DIR}/generator.cuh)

add_executable(CUDAGLFractal  ${GLAD_FILES} ${SHADERMAN_FILES} ${VIEW_FILES} ${CONTROLLER_FILES} ${GENERATOR_FILES} ./src/main.cpp)

# library includes
target_include_directories(CUDAGLFractal PRIVATE ${GLAD_DIR})
target_include_directories(CUDAGLFractal PRIVATE ${SHADERMAN_DIR})
target_include_directories(CUDAGLFractal PRIVATE ${VIEW_DIR})
target_include_directories(CUDAGLFractal PRIVATE ${CONTROLLER_DIR})

# GLFW Linking
add_subdirectory(./glfw-3.4/)
target_include_directories(CUDAGLFractal PRIVATE ./glfw-3.4/include/)
target_link_libraries(CUDAGLFractal glfw ${GLFW_LIBRARIES})
