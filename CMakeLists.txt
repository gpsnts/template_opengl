cmake_minimum_required(VERSION 3.16)
project(app VERSION 1.0)

set (CMAKE_CXX_STANDARD 20)

# set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
# set(HEADERS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/headers)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Settings.cmake)
add_executable(${PROJECT_NAME})
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Libraries.cmake)
include_directories(${HEADERS_DIR})

option(DEBUG_MODE "Show logs in debug mode" OFF)

if(DEBUG_MODE)
	message("Rodando em DEBUG_MODE\n")
  add_definitions(-DDEBUG_MODE)
else()
	message("Rodando em modo sem logs (!DEBUG_MODE)")
endif()

target_include_directories(
  ${PROJECT_NAME}
	PRIVATE
  ${LIBS_INCLUDES}
)

target_sources(
  ${PROJECT_NAME}
  PRIVATE
  ${SRCS}
  ${HEADERS}
  ${HEADERS_PCH}
)

target_precompile_headers(
  ${PROJECT_NAME}
  PRIVATE
  ${HEADERS_PCH}
)