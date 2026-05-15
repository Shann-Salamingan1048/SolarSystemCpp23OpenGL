cmake_minimum_required(VERSION 3.28)

project(SolarSystem LANGUAGES C CXX)

# --------------------------------------------------
# C++ Standard
# --------------------------------------------------

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# --------------------------------------------------
# Source Files
# --------------------------------------------------
# Non-modules version:
# Use .hpp/.cpp instead of .cppm/import/export module.

set(SOURCE_FILES
        main.cpp
        core/src/glad.c

        Camera.cpp
        Engine/Engine.cpp
        SolarSystem.cpp

        Shapes/BaseShape3D.cpp
        Shapes/Sphere.cpp

        Shader.cpp
        vao.cpp
        vbo.cpp
        ebo.cpp
        Texture.cpp

        Renderer/Renderer.cpp

        Utilities/globalFunctions.hpp
        Utilities/TimeUtils.hpp
        Utilities/ResourceManager.cpp
        Utilities/DefaultValues.hpp

        CelestialBodies/CelestialBody.hpp
        CelestialBodies/Planet.cpp
)

add_executable(SolarSystem ${SOURCE_FILES})

# --------------------------------------------------
# Include Directories
# --------------------------------------------------

target_include_directories(SolarSystem
        PRIVATE
        ${CMAKE_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/core/include
)

# --------------------------------------------------
# Assets
# --------------------------------------------------

add_custom_target(sync_assets ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/glsl
        $<TARGET_FILE_DIR:SolarSystem>/glsl

        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/Pics
        $<TARGET_FILE_DIR:SolarSystem>/Pics

        COMMENT "Syncing shader and texture assets..."
)

add_dependencies(SolarSystem sync_assets)

# --------------------------------------------------
# Platform Libraries
# --------------------------------------------------

if(WIN32)

    target_link_libraries(SolarSystem
            PRIVATE
            "${CMAKE_SOURCE_DIR}/core/lib/glfw3.lib"
            opengl32
            gdi32
            user32
            shell32
    )

else()

    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GLFW REQUIRED glfw3)
    find_package(OpenGL REQUIRED)

    target_include_directories(SolarSystem
            PRIVATE
            ${GLFW_INCLUDE_DIRS}
    )

    target_link_directories(SolarSystem
            PRIVATE
            ${GLFW_LIBRARY_DIRS}
    )

    target_link_libraries(SolarSystem
            PRIVATE
            ${GLFW_LIBRARIES}
            OpenGL::GL
            dl
            pthread
    )

endif()