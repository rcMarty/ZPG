cmake_minimum_required(VERSION 3.27)
project(ZPG)


set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra ")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -fsanitize=address")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2 -pedantic -flto -march=native -mtune=native")

add_compile_definitions(ZPG_SAFE_PIXEL_ACCESS)
add_compile_definitions(ZPG_PERF)

if (CMAKE_BUILD_TYPE MATCHES Debug)
    add_compile_definitions(ZPG_DEBUG)
    message("BUILDING WITH DEBUG MODE")
endif ()

set(OUTPUT_DIR "${CMAKE_BINARY_DIR}")


add_executable(ZPG
        main.cpp
        engine/engine.cpp
        shader/shader.cpp
        render/scene.cpp
        object/mesh.cpp
        object/renderable_object.cpp
        render/window.cpp
        object/transform/transform.cpp
        object/transform/transform.h
        object/transform/translation.cpp
        object/transform/translation.h
        object/transform/rotation.cpp
        object/transform/rotation.h
        object/transform/scale.cpp
        object/transform/scale.h
        object/transform/transform_node.cpp
        object/transform/transform_node.h


)


find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)
find_package(assimp REQUIRED)


target_link_libraries(ZPG GLEW::glew)
target_link_libraries(ZPG glfw)
target_link_libraries(ZPG OpenGL::GL)
target_link_libraries(ZPG glm)
target_link_libraries(ZPG assimp)


