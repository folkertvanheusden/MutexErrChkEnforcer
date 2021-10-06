# (C) 2021 by folkert@vanheusden.com
# released under apache license v2.0

cmake_minimum_required(VERSION 3.9.4)

project(mutexerrchkenforcer VERSION 0.1)

set(CMAKE_BUILD_TYPE Debug)

add_library(mutexerrchkenforcer SHARED
	mutexerrchkenforcer.c
	)

target_compile_features(mutexerrchkenforcer PUBLIC c_std_99)

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads)
target_link_libraries(mutexerrchkenforcer Threads::Threads)

target_link_libraries(mutexerrchkenforcer -ldl)
target_link_libraries(mutexerrchkenforcer -rdynamic)

target_compile_options(mutexerrchkenforcer PRIVATE "-Wall")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Ofast -ggdb3")
