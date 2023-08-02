cmake_minimum_required(VERSION 3.23)
project(bmftohex VERSION 0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

list(APPEND LIBSRC bmfconvert.cpp)
add_library(bmfconvert SHARED ${LIBSRC})
target_include_directories(bmfconvert PUBLIC include)

list(APPEND SRC bmftohex.cpp)

add_executable(bmftohex ${SRC})
target_include_directories(bmftohex PRIVATE argparse/include)
target_link_libraries(bmftohex PRIVATE bmfconvert)
