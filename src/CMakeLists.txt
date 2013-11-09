set(restful_SRCS
    collection.cpp
    connectionhandler.cpp
    resource.cpp
    server.cpp
)


# qt5_wrap_cpp(agatha-server_MOC_HDRS ${agatha-server_HDRS})

# final lib
# add_executable(agatha-server ${agatha-server_SRCS})
add_library(restful STATIC ${restful_SRCS})

qt5_use_modules(restful Core Network)

# link lib with Qt libs
target_link_libraries(restful)
