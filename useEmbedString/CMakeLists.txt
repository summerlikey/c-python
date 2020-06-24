cmake_minimum_required(VERSION 3.0)
project(useEmbedString)

set(CMAKE_CXX_STANDARD 11)


#指定库路径
file(GLOB_RECURSE Python3.6_LIB "/usr/lib/python3.6/config-3.6m-x86_64-linux-gnu/*.so")

set(THIRD_PARTY_LIBS
    ${Python3.6_LIB}
)

set(THIRD_INCLUDE_DIRS
    "/usr/include/python3.6"
)

set(INTERNAL_LIB

)

set(INTERNAL_INCLUDE
        ${PROJECT_SOURCE_DIR}
)

include_directories(
        ${INTERNAL_INCLUDE}
        ${THIRD_INCLUDE_DIRS})

link_libraries(${INTERNAL_LIB} ${THIRD_PARTY_LIBS})
# 通常这样设置就可以，如果你的项目包含qrc文件，那么需要将它们单独添加进来


add_executable(${PROJECT_NAME} useEmbedString.cpp)
#添加库文件到工程
target_link_libraries(${PROJECT_NAME}  ${THIRD_PARTY_LIBS} ${INTERNAL_LIB})


