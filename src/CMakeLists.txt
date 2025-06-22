file(GLOB_RECURSE SRC_FILES "*.cpp" "*.c")

add_executable(JotaEngine ${SRC_FILES})

target_include_directories(JotaEngine PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/external/imgui 
    ${CMAKE_SOURCE_DIR}/external/imgui/backends
    ${CMAKE_SOURCE_DIR}/external/stb
)

target_link_libraries(JotaEngine PRIVATE
    imgui
    glfw
    assimp
    ${OPENGL_LIBRARIES}
)

message(STATUS "Assimp found at: ${ASSIMP_LIBRARIES}")