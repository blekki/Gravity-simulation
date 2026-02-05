find_package(GTest REQUIRED)

set(AUTO_TEST_NAME auto_test)
set(TESTS_SOURCES
    test_particle.cpp
    # test_gravity.cpp
)

add_executable(${AUTO_TEST_NAME} ${TESTS_SOURCES})
target_link_libraries(${AUTO_TEST_NAME} PUBLIC static_lib ${LIBS} GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(${AUTO_TEST_NAME})