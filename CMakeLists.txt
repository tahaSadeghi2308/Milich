project(wms)

include_directories(include)

add_executable(run main.cpp src/users.cpp src/shortFuncs.cpp src/memoryManager.cpp src/productManager.cpp)
