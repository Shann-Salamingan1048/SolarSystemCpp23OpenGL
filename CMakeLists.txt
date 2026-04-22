cmake_minimum_required(VERSION 3.28)

project(SolarSystem LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-fmodules-ts)
endif()

set(SOURCE_FILES
        main.cpp
        core/src/glad.c
)
set(MODULE_INTERFACE_FILES
        Camera.cppm
        Engine/Engine.cppm
        SolarSystem.cppm
        Shapes/BaseShape3D.cppm
        Shapes/Sphere.cppm
        Shader.cppm
        vao.cppm
        vbo.cppm
        ebo.cppm
        Texture.cppm
        Utilities/globalFunctions.cppm
        Utilities/TimeUtils.cppm
        Utilities/ResourceManager.cppm
        Utilities/DefaultValues.cppm
        Renderer/Renderer.cppm
        CelestialBodies/CelestialBody.cppm
        CelestialBodies/Planet.cppm

)

set(MODULE_IMPLEMENTATION_FILES
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
        Utilities/ResourceManager.cpp
        CelestialBodies/Planet.cpp
)
add_executable(SolarSystem)

target_sources(SolarSystem
        PRIVATE
        ${SOURCE_FILES}
        ${MODULE_IMPLEMENTATION_FILES}

        PUBLIC
        FILE_SET CXX_MODULES FILES
        ${MODULE_INTERFACE_FILES}
)

target_include_directories(SolarSystem
        PRIVATE
        ${CMAKE_SOURCE_DIR}/core/include
)

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

    target_include_directories(SolarSystem PRIVATE ${GLFW_INCLUDE_DIRS})
    target_link_directories(SolarSystem PRIVATE ${GLFW_LIBRARY_DIRS})
    target_link_libraries(SolarSystem
            PRIVATE
            ${GLFW_LIBRARIES}
            OpenGL::GL
            dl
            pthread
    )
endif()