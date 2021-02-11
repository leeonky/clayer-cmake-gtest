cmake_minimum_required (VERSION 3.16)

project(sysport)

include(../cmake/shared-lib.cmake)

shared_lib()

define_test_runner(test/sysport_test.cc)
mock_sys_call(
        sem_open
        sem_unlink
        sem_close
)
add_sources(
        sysport.c
)
add_test_runner()

