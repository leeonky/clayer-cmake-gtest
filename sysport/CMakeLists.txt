aux_source_directory(. SOURCE_DIR)

add_library (sysport SHARED ${SOURCE_DIR})

# For test
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

aux_source_directory(./test TEST_DIR)

add_executable (run-tests ${TEST_DIR})
target_link_libraries(run-tests ${GTEST_LIBRARIES} pthread)

