cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(ProjectName)

# Find the ignition-common library
set(IGN_COMMON_VER 4)
find_package(ignition-common${IGN_COMMON_VER} REQUIRED COMPONENTS events profiler)

add_executable(assert_example assert_example.cc)
target_link_libraries(assert_example ignition-common${IGN_COMMON_VER}::core)

add_executable(console_example console.cc)
target_link_libraries(console_example ignition-common${IGN_COMMON_VER}::core)

add_executable(events_example events.cc)
target_link_libraries(events_example ignition-common${IGN_COMMON_VER}::events)
