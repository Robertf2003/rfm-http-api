#include "exceptions.hpp"
#include <curl/curl.h>

const char* CurlInitializeFailure::what() {
  return "CURL failed to initialize";
}

CurlHeaderFailure::CurlHeaderFailure(CURLcode curl_code) {
  CurlHeaderFailure::curl_code = curl_code;
}

CURLcode CurlHeaderFailure::get_error_code() {
  return CurlHeaderFailure::curl_code;
}
const char* CurlHeaderFailure::what() {
  return "CURL failed to add header";
}

CURLcode CurlPerformFailure::get_error_code() {
  return CurlPerformFailure::curl_code;
}
const char* CurlPerformFailure::what() {
  return "CURL failed to perform request";
}

