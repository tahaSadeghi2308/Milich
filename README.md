# MILICH
Milich is a simple product manager system that allows you to manage your products using a command line
interface (CLI) system .
this project has been created with a system which is so hard to type with it !!!!

## HOW TO RUN
First make sure you have installed g++/gcc and cmake build system and than run following commands
```sh
rm -rf build
mkdir build && cd build
cmake ..
make
./run
```

if you are using windows use these commands 

```cmd
rmdir /s /q build
mkdir build
cd build
cmake ..
mingw32-make
.\run
```

if you haven't cmake , you can run this program with this instruction

```
g++ main.cpp src/usersManager.cpp src/shortFuncs.cpp src/productManager.cpp -o run
./run
