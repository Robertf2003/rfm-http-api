cmake_minimum_required(VERSION 3.30)
project(apifetcher CXX)

set(SOURCES)
set(SOURCES 
src/curl-api-json-fetcher.cpp
src/exceptions.cpp)


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(apifetcher SHARED
  ${SOURCES})
target_include_directories(apifetcher PUBLIC include)


set(APIFETCHER_LIST_OF_HEADERS
  "include/curl-api-json-fetcher.hpp"
  "include/api-json-fetch.hpp"
  "include/exceptions.hpp"
)
set_target_properties(apifetcher PROPERTIES PUBLIC_HEADER "${APIFETCHER_LIST_OF_HEADERS}")

# Find the required packages 
find_package(CURL REQUIRED)

# Link packages to target
target_link_libraries(apifetcher CURL::libcurl)

install(TARGETS apifetcher
        PUBLIC_HEADER DESTINATION "include")
