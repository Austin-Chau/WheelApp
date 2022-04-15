message("List of sources")
add_executable(wheelTester mainTester.cpp RewardTester.cpp)

add_test(NAME wheelTester COMMAND ${APP_NAME})

target_link_libraries(wheelTester PUBLIC ${APP_NAME} gtest)
