cmake_minimum_required(VERSION 2.8)

#Name of the project
project(SBRP)

#Include the header and the source files
include_directories(include)
file(GLOB SOURCES "src/*.cpp")

#Gurobi folder
set(GUROBI_F "/opt/gurobi651/linux64")

#LocalSolver folder
set(LOCALSOLVER_F "/opt/localsolver_6_0")

#Include Gurobi files
include_directories("${GUROBI_F}/include")

#Include LocalSolver files
include_directories("${LOCALSOLVER_F}/include")

#Executable of the project
add_executable(SBRP ${SOURCES})

#Flags used during the linking time
set(CMAKE_SHARED_LINKER_FLAGS "-L${GUROBI_F}/lib -lpthread -lgurobi_c++ -lgurobi65")

#Include the flags o be used during linking time
target_link_libraries(SBRP ${CMAKE_SHARED_LINKER_FLAGS})
