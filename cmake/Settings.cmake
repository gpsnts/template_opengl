set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(VERSION_MAJOR 0)
set(VERSION_MINOR 0)
set(VERSION_FEATURE 1)

set(VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_FEATURE}")
message("\nProject version: ${VERSION}\n")

file(
  GLOB
  SRCS
  CONFIGURE_DEPENDS
  ${SRC_DIR}/*.cpp
)

file(
  GLOB
  HEADERS_PCH
  CONFIGURE_DEPENDS
  ${SRC_DIR}/headers/pch/*.hpp
)

file(
  GLOB
  HEADERS
  CONFIGURE_DEPENDS
  ${SRC_DIR}/headers/*.hpp
)

message("Compiler settings...OK\n")