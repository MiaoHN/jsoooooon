cmake_minimum_required(VERSION 3.10)
project(jsoooooon)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

include_directories(include)

file(GLOB SRC_FILES 
  "src/*.cpp"
  )

add_library(${PROJECT_NAME} ${SRC_FILES})

add_subdirectory(test)
