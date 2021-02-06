
function(shared_lib)
	project(${CMAKE_PROJECT_NAME})
	aux_source_directory(. PATH_SOURCE)

	add_library (${CMAKE_PROJECT_NAME} SHARED ${PATH_SOURCE})

	# For test
	find_package(GTest REQUIRED)
	include_directories(${GTEST_INCLUDE_DIRS})

	aux_source_directory(./test PATH_TEST)

	add_executable (${CMAKE_PROJECT_NAME}.tests ${PATH_TEST})
	target_link_libraries(${CMAKE_PROJECT_NAME}.tests ${GTEST_LIBRARIES} pthread)
	add_test(${CMAKE_PROJECT_NAME} ${CMAKE_PROJECT_NAME}.tests)
endfunction()

