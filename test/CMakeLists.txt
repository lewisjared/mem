
link_directories(${CMAKE_BUILD_DIR})

add_executable(testCpp testCpp.cpp)
target_link_libraries(testCpp mem)
