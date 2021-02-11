cmake_minimum_required (VERSION 3.16)

project(sysport)

include(../cmake/shared-lib.cmake)

shared_lib()

define_test_runner(test/sysport_test.cc)
add_test_runner()

