macro(shared_lib)
	aux_source_directory(. PATH_SOURCE)

	add_library (${PROJECT_NAME} SHARED ${PATH_SOURCE})
endmacro()

macro(define_test_runner source)
    set(runner_source ${source})
endmacro()

macro(add_test_runner)
	find_package(GTest REQUIRED)
	include_directories(${GTEST_INCLUDE_DIRS})

	string(REPLACE test/ "" main_target ${runner_source})
	set(main_target ${main_target}.tests)
	add_executable (${main_target} ${runner_source})
	target_link_libraries(${main_target} ${GTEST_LIBRARIES} pthread)
	add_test(${main_target} ${main_target})
endmacro()
