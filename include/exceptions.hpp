/**
 * @file exceptions.hpp
 * @brief A list of possible exceptions that can occur when using the curling library
 */

#include <curl/curl.h>
#include <exception>
#pragma once

/**
 * @class CurlInitializeFailure
 * @brief An Exception that indicates that curl failed to initialize
 */
class CurlInitializeFailure : public std::exception {
  private:
    CURLcode curl_code;
  public:
    const char* what();
};

/**
 * @class CurlHeaderFailure
 * @brief An Exception that indicates that the header could not
 */
class CurlHeaderFailure : public std::exception {
  private:
    CURLcode curl_code;
  public:
    /**
     * @brief Creates the exception
     *
     * @param error_code The error code associated with the failure of the header
     */
    CurlHeaderFailure(CURLcode error_code);
    CURLcode get_error_code();
    const char* what();
};

/**
 * @class CurlPerformFailure
 * @brief An Exception that indicates that curl failed to perform a request
 */
class CurlPerformFailure : public std::exception {
  private:
    CURLcode curl_code;
  public:
    /**
     * @brief Creates the exception
     *
     * @param error_code The error code associated with the failure of perform the request
     */
    CurlPerformFailure(CURLcode error_code);
    CURLcode get_error_code();
    const char* what();
};
