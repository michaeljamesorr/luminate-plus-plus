add_executable (luminate-test test.cpp)
target_link_libraries(luminate-test luminate-lib GLEW GLU GL glfw gtest_main)
add_test(NAME LuminateTests COMMAND luminate-test)