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

#file(GLOB_RECURSE ZPG_src "src/*.cpp" "src/*.h")

set(SOURCE_FILES
        utils/observer.h
        render/scene.h
        render/scene.cpp
        render/window.h
        render/window.cpp
        object/model/mesh.h
        object/model/mesh.cpp
        object/renderable_object.h
        object/renderable_object.cpp
        object/camera/camera.h
        object/camera/camera.cpp
        input_handle/input_handler.h
        engine/engine.h
        engine/engine.cpp
        main.cpp


)


add_executable(ZPG
        main.cpp
        engine/engine.cpp
        shader/base_shader.cpp
        render/scene.cpp
        object/model/mesh.cpp
        object/renderable_object.cpp
        render/window.cpp
        object/camera/camera.cpp
        utils/observer.h
        object/light/point_light.cpp
        object/light/point_light.h
        shader/shader_wrapper.h
        shader/shader_wrapper.cpp
        object/material.cpp
        object/material.h
        object/light/light_wrapper.cpp
        object/light/light_wrapper.h
        object/light/directional_light.cpp
        object/light/directional_light.h
        object/light/spot_light.cpp
        object/light/spot_light.h
        object/light/light.cpp
        object/light/light.h
        object/transformable_object.cpp
        object/transformable_object.h
        utils/subject.h
        object/model/texture.cpp
        object/model/texture.h
        object/skybox/sky_box.cpp
        object/skybox/sky_box.h
        object/skybox/sky_dome.cpp
        object/skybox/sky_dome.h
        object/transform/bezier.h
        object/transform/bezier_curve.h

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


## TEST FOR HEADER FILES
find_file(STB_IMAGE_H "stb/stb_image.h")
if (NOT STB_IMAGE_H)
    message(FATAL_ERROR "stb/stb_image.h not found")
endif ()


