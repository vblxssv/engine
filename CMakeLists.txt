cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(NAME z)
project(${NAME})


file(GLOB_RECURSE SRC_FILES 
    "src/*.cpp" 
    "src/*.h" 
    "src/*.hpp"
)


add_executable(${NAME} ${SRC_FILES}
        src/graphics/VBO.cpp
        src/graphics/Mesh.cpp
        src/graphics/Mesh.h
        src/graphics/MeshFactory.cpp
        src/graphics/MeshFactory.h)


# папка src является корнем для поиска заголовков
target_include_directories(${NAME} PRIVATE src)

# 4. Настройки зависимостей (GLFW)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE) 
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE) 
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) 
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)
add_subdirectory(external/glad)
add_subdirectory(external/glm)


target_link_libraries(${NAME} PRIVATE glfw glad glm)

add_custom_command(TARGET ${NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/res"
    "$<TARGET_FILE_DIR:${NAME}>/res"
)