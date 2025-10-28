cmake_minimum_required(VERSION 3.10)

set(NAME z)

project(${NAME})


file(GLOB_RECURSE CPP_FILES src/*.cpp)
file(GLOB_RECURSE H_FILES   src/*.h src/*.hpp)


set(SRC_FILES ${CPP_FILES} ${H_FILES})

add_executable(${NAME} ${SRC_FILES})

set (GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE) 
set (GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE) 
set (GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) 
set (GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)
target_link_libraries(${NAME} glfw)

add_subdirectory(external/glad)
target_link_libraries(${NAME} glad)

add_subdirectory(external/glm)
target_link_libraries(${NAME} glm)

add_custom_command(TARGET ${NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/res
    $<TARGET_FILE_DIR:${NAME}>/res
)