cmake_minimum_required(VERSION 3.27)
project(untitled)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc")
set(SFML_STATIC_LIBRARIES TRUE)

add_executable(untitled main.cpp
        graph.h
        graph.cpp
        kruskal_algorithm.h
        kruskal_algorithm.cpp
        bfs.h
        bfs.cpp
        dfs.h
        dfs.cpp
        prima_algorithm.h
        prima_algorithm.cpp
)

set(SFML_DIR "C:\\Users\\D\\CLionProjects\\lib\\SFML\\GCC 7.3.0 MinGW (SEH) - 64-bit\\SFML-2.5.1\\lib\\cmake\\SFML")

target_link_libraries(untitled sfml-graphics)
target_include_directories(untitled PUBLIC "C:\\Users\\D\\CLionProjects\\lib\\SFML\\GCC 7.3.0 MinGW (SEH) - 64-bit\\SFML-2.5.1\\include")

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML 2.5 REQUIRED graphics network audio window system)