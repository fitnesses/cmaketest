cmake_minimum_required(VERSION 3.0)
project(hello VERSION 1.0.2)


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)

SET(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE) 
SET(CMAKE_INSTALL_RPATH "\${ORIGIN}/../lib")

include(cmake/utils.cmake)

string(TIMESTAMP BUILD_TIMESTAMP "%Y-%m-%d %H:%M:%S")
message("Build timestamp is ${BUILD_TIMESTAMP}")


set(GIT_HASH "")
get_git_hash(GIT_HASH)
message("Git hash is ${GIT_HASH}")

set(GIT_BRANCH "")
get_git_branch(GIT_BRANCH)
message("Git branch is ${GIT_BRANCH}")


option(FOO_ENABLE "Enable Foo" ON)
if(FOO_ENABLE)
  set(FOO_STRING "foo")
endif()

# 指定版本号的配置文件
configure_file(config.h.in config.h)

# list(APPEND EXTRA_LIBS xxx)
# list(APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/xxx")
# target_link_libraries(xxxx PUBLIC ${EXTRA_LIBS})
# target_include_directories(xxxx PUBLIC "${PROJECT_BINARY_DIR}" ${EXTRA_INCLUDES})

add_executable(${PROJECT_NAME} src/main.cpp)


target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_BINARY_DIR}")

add_subdirectory(src/adder)

# find_package(fmt REQUIRED)

link_directories(lib)

target_link_libraries(${PROJECT_NAME} PRIVATE
    fmt adder
)