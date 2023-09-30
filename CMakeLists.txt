cmake_minimum_required(VERSION 3.27)
project(ZPG)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra ")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -fsanitize=address")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2 -pedantic -flto -march=native -mtune=native")

add_compile_definitions(ZPG_SAFE_PIXEL_ACCESS)
add_compile_definitions(ZPG_PERF)

if(CMAKE_BUILD_TYPE MATCHES Debug)
    add_compile_definitions(ZPG_DEBUG)
    message("BUILDING WITH DEBUG MODE")
endif()

set(OUTPUT_DIR "${CMAKE_BINARY_DIR}")


add_executable(ZPG
        main.cpp
        engine/engine.cpp
        shader/shader.cpp
        render/scene.cpp
        object/mesh.cpp
        object/renderable_object.cpp
        object/renderable_object.h


)



find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)


target_link_libraries(ZPG GLEW::glew)
target_link_libraries(ZPG glfw)
target_link_libraries(ZPG OpenGL::GL)
target_link_libraries(ZPG glm)


