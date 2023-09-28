cmake_minimum_required(VERSION 3.27)
project(ZPG)

set(CMAKE_CXX_STANDARD 17)


#link_directories(${CMAKE_BINARY_DIR}/lib)
#target_include_directories(ZPG PUBLIC /home/rc_marty/_Škola/5_Semestr/ZPG/lib/)


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

#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR}/lib)
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR}/lib)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})

#add_subdirectory(lib)


add_executable(ZPG
        main.cpp)




#target_link_libraries(ZPG {CMAKE_BINARY_DIR}/lib/glfw-3.3.8/build/src)
#target_link_libraries(ZPG REQUIRED OpenGL::GL)
#target_link_libraries(ZPG REQUIRED GLFW)

find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)


target_link_libraries(ZPG GLEW::glew)
target_link_libraries(ZPG glfw)
target_link_libraries(ZPG OpenGL::GL)
target_link_libraries(ZPG glm)



## /home/rc_marty/_Škola/5_Semestr/ZPG/lib/glfw-3.3.8/include)
##/home/rc_marty/_Škola/5_Semestr/ZPG/lib/glm-master


#target_link_libraries(ZPG -lGL -lGLU -lglut -lGLEW -lSOIL -lassimp)

#set(glm_DIR /home/rc_marty/_Škola/5_Semestr/ZPG/lib/glm-master/glm/)
#find_package(glm REQUIRED)
#target_link_libraries(ZPG glm::glm)


#target_include_directories(ZPG PUBLIC /home/rc_marty/_Škola/5_Semestr/ZPG/lib/glm-master)

#target_link_libraries(ZPG /home/rc_marty/_Škola/5_Semestr/ZPG/lib/glfw-3.3.8/src/libglfw3.a)
#target_link_libraries(ZPG /home/rc_marty/_Škola/5_Semestr/ZPG/lib/glm-master/glm/glm.hpp)
