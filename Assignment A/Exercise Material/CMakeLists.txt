SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -pedantic")
include_directories(".")

#add_executable( matrix Matrix.cpp)
#add_executable( MatrixTest MatrixTest.cpp)
#add_executable( MatrixProduct MatrixProduct.cpp)
add_executable( tests tests.cpp) 