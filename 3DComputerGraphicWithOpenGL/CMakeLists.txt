cmake_minimum_required(VERSION 3.21)
project(3DComputerGraphicWithOpenGL LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# vcpkg 패키지
find_package(fmt CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

# 소스 파일만 모으기 (헤더는 포함하지 않음)
file(GLOB_RECURSE PROJECT_SOURCES
    Source/*.cpp
)

add_executable(3DComputerGraphicWithOpenGL ${PROJECT_SOURCES})

# 라이브러리 연결
target_link_libraries(3DComputerGraphicWithOpenGL
    PRIVATE
        fmt::fmt
        glad::glad
        glfw
        imgui::imgui
)

target_include_directories(3DComputerGraphicWithOpenGL PRIVATE
    ${CMAKE_SOURCE_DIR}/
    ${CMAKE_SOURCE_DIR}/Source
    ${CMAKE_SOURCE_DIR}/Include
    ${CMAKE_SOURCE_DIR}/Include/ImGui/Backends 
    ${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/include
)

target_sources(3DComputerGraphicWithOpenGL PRIVATE
    ${CMAKE_SOURCE_DIR}/Include/ImGui/Backends/imgui_impl_glfw.cpp
    ${CMAKE_SOURCE_DIR}/Include/ImGui/Backends/imgui_impl_opengl3.cpp
)

target_compile_definitions(3DComputerGraphicWithOpenGL PRIVATE
    IMGUI_IMPL_OPENGL_LOADER_GLAD
)