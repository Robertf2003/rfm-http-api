cmake_minimum_required(VERSION 3.15)
project(PackageTest CXX)

find_package(rfm_http_requester CONFIG REQUIRED)

add_executable(example src/example.cpp)
target_link_libraries(example rfm_http_requester::rfm_http_requester)
