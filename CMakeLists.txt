cmake_minimum_required(VERSION 3.10)

set(NAME z)

project(${NAME})

add_executable(${NAME} 
    src/main.cpp
    src/ResourceManager/ResourceManager.h
    src/ResourceManager/ResourceManager.cpp
    src/math/math.h
    src/math/math.cpp
    src/memory/VAO.h
    src/memory/VAO.cpp
    src/memory/VBO.h
    src/memory/VBO.cpp
    src/memory/EBO.h
    src/memory/EBO.cpp
    src/camera/Camera.h
    src/camera/Camera.cpp
    src/IO/Cursor.h
    src/IO/Cursor.cpp
    src/screen/Screen.h
    src/screen/Screen.cpp
    external/stb_image/stb_image.h
    src/geometry/Geometry.h
    src/geometry/Geometry.cpp
    src/object3d/Object3d.h
    src/object3d/Object3d.cpp
    src/attribute/Attribute.h
    src/attribute/Attribute.cpp
    src/framelimiter/FrameLimiter.h
    src/framelimiter/FrameLimiter.cpp
    src/application/Application.h
    src/application/Application.cpp
    src/event/Event.h
    src/event/Event.cpp
    src/ssbo/SSBO.h
    src/ssbo/SSBO.cpp
    src/scene/Scene.h
    src/scene/Scene.cpp
    src/keyboard/Keyboard.h
    src/keyboard/Keyboard.cpp
    src/resource/Resource.h
src/resource/Shader.cpp
src/resource/Texture.cpp
src/resourceLoader/ShaderLoader.h
src/resourceLoader/TextureLoader.h
src/resourceLoader/ShaderLoader.cpp
src/resourceLoader/TextureLoader.cpp
)



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