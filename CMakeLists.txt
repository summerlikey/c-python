cmake_minimum_required(VERSION 3.0)
project(cpp-python-sample)

set(CMAKE_CXX_FLAGS "-std=c++11")

# 加入各子工程
add_subdirectory(usePythonScript)
add_subdirectory(useEmbed)

