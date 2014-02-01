set(restful_SRCS
    collection.cpp
    connectionhandler.cpp
    server.cpp
)

# final lib
add_library(restful STATIC ${restful_SRCS})

qt5_use_modules(restful Core Network)

# link lib with Qt libs
target_link_libraries(restful)
