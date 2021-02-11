macro(shared_lib)
	include_directories(../libs/)
	aux_source_directory(. PATH_SOURCE)

	add_library (${PROJECT_NAME} SHARED ${PATH_SOURCE})
endmacro()

macro(define_test_runner source)
    set(runner_source ${source})
endmacro()

macro(add_test_runner)
	string(REPLACE test/ "" main_target ${runner_source})
	set(main_target ${main_target}.tests)

	list(PREPEND source_codes ${runner_source})
	add_executable (${main_target} ${source_codes})
	target_link_libraries(${main_target} gtest gtest_main)

    set(wraps "")
    foreach(function IN LISTS mock_functions)
		set(wraps "${wraps} -Wl,--wrap=${function}")
	endforeach()
	set_property(TARGET ${main_target} APPEND PROPERTY LINK_FLAGS "${wraps}")

	add_test(${main_target} ${main_target})
endmacro()

macro(mock_sys_call function)
	set(mock_functions ${ARGN})
	list(PREPEND mock_functions ${function})
endmacro()

macro(add_sources file)
	set(source_codes ${ARGN})
	list(PREPEND source_codes ${file})
endmacro()
