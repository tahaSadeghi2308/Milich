project(wms)

include_directories(include)

add_executable(run main.cpp src/usersManager.cpp src/shortFuncs.cpp src/productManager.cpp)
