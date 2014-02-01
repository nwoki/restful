project(testapp CXX)

cmake_minimum_required(VERSION 2.8.9)

find_package(Qt5 COMPONENTS Core Network)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../includes/)


set(CMAKE_AUTOMOC TRUE)
set(CMAKE_INCLUDE_CURRENT_DIR ON)


set(testapp_SRCS
    main.cpp
    mycollection.cpp
)


# final lib
add_executable(testapp ${testapp_SRCS})

# link lib with Qt libs
target_link_libraries(testapp restful)

