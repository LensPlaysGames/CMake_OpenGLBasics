cmake_minimum_required (VERSION 3.8)

set(SOURCE_FILES 
    "Camera.cpp" 
    "FPSTimer.cpp" 
    "Mesh.cpp" 
    "Model.cpp" 
    "Object.cpp" 
    "Renderer.cpp" 
    "Shader.cpp" 
    "Timer.cpp" 
    "Source.cpp" 
    "../imgui/imgui.cpp" 
    "../imgui/imgui_demo.cpp"
    "../imgui/imgui_draw.cpp" 
    "../imgui/imgui_impl_glfw.cpp"
    "../imgui/imgui_impl_opengl3.cpp"
    "../imgui/imgui_tables.cpp"
    "../imgui/imgui_widgets.cpp"
 "RAMTracker.cpp")

set(HEADER_FILES 
    "Primitives.h" 
    "Camera.h" 
    "FPSTimer.h" 
    "Mesh.h" 
    "Model.h" 
    "Object.h" 
    "Renderer.h" 
    "Shader.h" 
    "Timer.h" 
    "ProgramMemory.h"
 "RAMTracker.h")

# Add source files to this project's executable.
add_executable (CMake_OpenGLBasics ${HEADER_FILES} ${SOURCE_FILES})

# Include necessary headers
target_include_directories(CMake_OpenGLBasics PUBLIC ${CMAKE_SOURCE_DIR}/imgui/)
target_include_directories(CMake_OpenGLBasics PUBLIC ${CMAKE_SOURCE_DIR}/glm)
target_include_directories(CMake_OpenGLBasics PUBLIC ${CMAKE_SOURCE_DIR}/glfw/include)
target_include_directories(CMake_OpenGLBasics PUBLIC ${CMAKE_SOURCE_DIR}/glew-cmake/include)
target_include_directories(CMake_OpenGLBasics PUBLIC ${CMAKE_SOURCE_DIR}/assimp/include)

# Link necessary libraries
target_link_libraries(CMake_OpenGLBasics libglew_static glfw assimp)

# Copy all dynamically linked libraries (.dll)
add_custom_command(TARGET CMake_OpenGLBasics POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/dlls"
        $<TARGET_FILE_DIR:CMake_OpenGLBasics>)

# Copy shaders
add_custom_command(TARGET CMake_OpenGLBasics POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/shaders"
        $<TARGET_FILE_DIR:CMake_OpenGLBasics>/../shaders/)

# Copy 3D Models
add_custom_command(TARGET CMake_OpenGLBasics POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/models"
        $<TARGET_FILE_DIR:CMake_OpenGLBasics>/../models/)