# Libraries location
set(LIBS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs)

# Libs path
set(STB_DIR ${LIBS_DIR}/stb)
set(FREETYPE_2_DIR ${LIBS_DIR}/freetype)

# OpenGL (Must be OS installed -- 4.6+ required)
set(OpenGL_GL_PREFERENCE "GLVND")                                
find_package(OpenGL REQUIRED)                                         
if(NOT OPENGL_FOUND)                                      
  message(OpenGL needed!)                                            
endif(NOT OPENGL_FOUND)

# GLAD
add_library(glad ${LIBS_DIR}/glad/src/glad.c)
target_include_directories(glad PRIVATE ${LIBS_DIR}/glad/include)

# FreeType2
set(FREETYPE_DIR ${LIBS_DIR}/freetype)
set(FREETYPE_LIBRARY freetype)
set(FREETYPE_LIBRARIES ${FREETYPE_LIBRARY})
set(FREETYPE_INCLUDE_DIRS ${FREETYPE_DIR}/include)
include_directories(${FREETYPE_INCLUDE_DIRS})
link_directories(${FREETYPE_DIR})

# ASSIMP
#message("Running assimp \n\n\n\n\n")
#add_subdirectory(${LIBS_DIR}/assimp)
#include_directories(${LIBS_DIR}/stb)
#set(ZLIB_LIBRARIES zlibstatic)
#set(ENABLE_BOOST_WORKAROUND ON)
#set(BUILD_STATIC_LIB ON)
#set(BUILD_ASSIMP_TOOLS  ON)
#set(ASSIMP_BUILD_STATIC_LIB ON)

# GLFW
add_subdirectory(${LIBS_DIR}/glfw)

# GLM
add_subdirectory(${LIBS_DIR}/glm)

# STB
include_directories(${LIBS_DIR}/stb)
link_directories(${LIBS_DIR}/stb)

target_link_libraries(
	${PROJECT_NAME}
	glad
	glfw
	glm
	${FREETYPE_LIBRARIES}
	#assimp
	${CMAKE_DL_LIBS}
)

file(
  GLOB
  LIBS_INCLUDES
  ${LIBS_DIR}/glad/include
	${FREETYPE_INCLUDE_DIRS}
  ${OpenGL_INCLUDE_DIRS}
)

message("\nLibs...OK\n")
