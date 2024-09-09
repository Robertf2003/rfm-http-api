cmake_minimum_required(VERSION 3.15)
project(rfm_http_requester CXX)

# Clear sources incase parent directory has some loaded
set(SOURCES)
set(SOURCES 
src/curl-api-json-fetcher.cpp
src/exceptions.cpp)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(APIFETCHER_LIST_OF_HEADERS
  include/curl-api-json-fetcher.hpp
  include/api-json-fetch.hpp
  include/exceptions.hpp
)

add_library(rfm_http_requester SHARED)

target_sources(rfm_http_requester
  PUBLIC
  src/curl-api-json-fetcher.cpp
  src/exceptions.cpp
)
target_include_directories(rfm_http_requester PUBLIC include)

get_target_property(OUT rfm_http_requester SOURCES)

set_target_properties(rfm_http_requester PROPERTIES PUBLIC_HEADER "${APIFETCHER_LIST_OF_HEADERS}")

# Find the required packages 
find_package(CURL REQUIRED)

# Link packages to target
target_link_libraries(rfm_http_requester CURL::libcurl)

install(TARGETS rfm_http_requester)
