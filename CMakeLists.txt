# ==============================================================================
# [SECTION 1] Project Configuration
# ==============================================================================
cmake_minimum_required(VERSION 3.15)
project(opengl_project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ==============================================================================
# [SECTION 2] Dependency Loading (Library Search via vcpkg)
# ==============================================================================
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)

# ==============================================================================
# [SECTION 3] Include Directories (Header Files)
# ==============================================================================
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/include/buffers)
include_directories(${CMAKE_SOURCE_DIR}/include/utils)
include_directories(${CMAKE_SOURCE_DIR}/include/graphics)
include_directories(${CMAKE_SOURCE_DIR}/include/graphics/textures)
include_directories(${CMAKE_SOURCE_DIR}/include/core)
include_directories(${STB_INCLUDE_DIRS})

# ==============================================================================
# [SECTION 4] Source Files Collection
# ==============================================================================
file(GLOB_RECURSE SOURCES "src/*.cpp")

# ==============================================================================
# [SECTION 5] Build Target (Executable)
# ==============================================================================
add_executable(${PROJECT_NAME} ${SOURCES})

# ==============================================================================
# [SECTION 6] Library Linking
# ==============================================================================
target_link_libraries(${PROJECT_NAME} PRIVATE
    glfw
    glad::glad
    glm::glm
    OpenGL::GL
    nlohmann_json::nlohmann_json
    ${CMAKE_DL_LIBS}
)