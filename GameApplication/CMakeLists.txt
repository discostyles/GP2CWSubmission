cmake_minimum_required (VERSION 2.8)
project (GameApplication)

set(CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -l")

find_package(TinyXML REQUIRED)
find_package(SDL2 REQUIRED)
find_package(OPENGL REQUIRED)
find_package(GLM REQUIRED)
find_package(GLEW REQUIRED)
find_package(SDL2_Image REQUIRED)
find_package(SDL2_TTF REQUIRED)
find_package(assimp REQUIRED)

add_subdirectory(Utils)

add_library(GameApplication STATIC src/RenderBuffer.cpp src/PostProcessing.cpp src/Camera.cpp src/ModelLoading.cpp src/GameObject.cpp src/GameApplication.cpp src/Shader.cpp src/Texture.cpp include/RenderBuffer.h include/PostProcessing.h include/Camera.h include/ModelLoading.h include/GameObject.h include/Common.h include/GameApplication.h include/Shader.h include/Texture.h include/Vertex.h)

include_directories(GameApplication include/ Utils/include ${ASSIMP_INCLUDE_DIR} ${TINYXML_INCLUDE_DIR} ${SDL2IMAGE_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR} ${SDL2_INCLUDE_DIR} ${OPENGL_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})
# create the program
target_link_libraries(GameApplication Utils ${ASSIMP_LIBRARIES} ${TINYXML_LIBRARIES} ${SDL2IMAGE_LIBRARY} ${SDL2_TTF_LIBRARIES} ${CMAKE_DL_LIBS} ${SDL2_LIBRARY} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES})
