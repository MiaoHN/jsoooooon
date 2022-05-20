cmake_minimum_required(VERSION 3.10)
project(jsoooooon)

include_directories(include)

file(GLOB SRC_FILES 
  "src/*.cpp"
  )

add_library(${PROJECT_NAME} ${SRC_FILES})

add_subdirectory(test)
