# cmake 学习
1. add_library 主要作用就是将指定的源文件生成链接文件，然后添加到工程中去;生成动态链接库或者静态库;一般是自己的项目大了，需要自己做 so 或者静态库；然后通过 target_link_libraries 加到自己的项目中

    ```
    add_library(${PROJECT_NAME} SHARED
        src/track/Tracking.cpp
    )
    ```

2. link_directories主要是指定要链接的库文件的路径。一般情况不需要可以通过 find_package 和 find_library找到库文件的绝对路径，不过自己写的动态库文件可以用这个方法找到

    ```
    link_directories(lib)
    ```

    ```
    find_package(fmt REQUIRED)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        fmt::fmt
    )
    ```

3. target_link_libraries将目标文件与库文件进行链接，target是指通过add_executable()和add_library()指令生成已经创建的目标文件。而[item]表示库文件没有后缀的名字。

    ```
    target_link_libraries(<target> [item1] [item2] [[debug|optimized|general]] ...)
    ```

4. Ninja?
5. target_include_directories(hello PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
6. GLOB 递归查找 cpp

    ```
    file(GLOB_RECURSE SRC_FILES src/*.cpp)
    add_executable(hello main.cpp ${SRC_FILES})
    ```

7. add_subdirectory, add_library 一起使用，子模块单独编译，然后被上层依赖 target_link_libraries
8. 第三方库,find 之后如果找到，会对应有相应的结果变量（_INCLUDE_DIR(S) , _LIBRARIES) 下面就可以直接使用

    ```
    find_package(SFML 2 REQUIRED network audio graphics window system) // 2版本
    target_include_directories(hello PUBLIC ${SFML_INCLUDE_DIR})
    target_link_libriaries(hello PUBLIC ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
    ```

9. 如果第三方库没有标准的 cmake 且不在/usr/lib 目录下

    ```
    find_library(MYLIB mylib PATHS /tmp/customPath)
    target_link_libraries(hello PUBLIC ${MYLIB})

    set(MYLIB_INCLUDE_DIRS /tmp/customPath/include)
    target_include_directories(hello PUBLIC ${MYLIB_INCLUDE_DIRS})
    ```

10. 第三方库在/usr/lib，不需要指定 path，因为默认就在系统/usr/lib查找

    ```
    find_library(MYLIB mylib)
    target_link_libraries(hello PUBLIC ${MYLIB})
    ```

11. cmake function, argn 未绑定 argv 所有

    ```
    function(do_cmake_good first_arg)
        message(STATUS "you caked tge ${first_arg}" )
    endfunction()

    do_cmake_good(1)
    ```

12. cmake 的作用域比较复杂，调用函数，其实是将调用之前的所有代码拷贝一遍， parent_scope 影响外面参数的值，做返回值用
13. https://www.youtube.com/watch?v=mBjRjZcRTA0 cmake 语法
14. config.h.in, @PROJECT_VERSION_MAJOR@ 关闭 clang-format 功能

    ```
    config_file(config.h.in config.h)
    target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_BINARY_DIR}")
    ```

15. include_directories 也可以添加头文件库

    ```
    link_directories(${Boost_INCLUDE_DIRS})
    ```

16. install 安装，将可执行文件或者文件安装到特定的目录中

    ```
    install(TARGETS thunder-trader DESTINATION bin)
    install(FILES thunder-trader.conf.default DESTINATION bin RENAME thunder-trader.conf)
    ```

17. debug，release 模式只是编译选项的不同，release 会做些优化，debug 主要目的在于便于定位问题

    ```
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
    set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb -std=c++11 -fno-strict-aliasing")
    set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall -std=c++11 -fno-strict-aliasing")
    ```

    ```
    cmake -DCMAKE_BUILD_TYPE=Release ../
    cmake -DCMAKE_BUILD_TYPE=Debug ../
    ```

18. make -j$(nproc)
19. option 用法， 未解决为啥 vscode warning invalid preprocesing directive;这个会有缓存的问题，最好删除 build 下的文件重新编译，否则可能不对

## 编译选项
1. -fPIC ：表示编译为位置独立的代码，用于编译共享库。目标文件需要创建成位置无关码，就是在可执行程序装载它们的时候，它们可以放在可执行程序的内存里的任何地方
2. -flto: 编译优化选项
3. -fvisibility=hidden 优化
4. -fno-strict-aliasing