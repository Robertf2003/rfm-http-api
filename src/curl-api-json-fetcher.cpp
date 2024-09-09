#include "curl-api-json-fetcher.hpp"
#include "api-json-fetch.hpp"
#include "exceptions.hpp"
#include <cstddef>
#include <cstring>
#include <curl/curl.h>
#include <curl/easy.h>
#include <iostream>
#include <memory>
#include <ostream>
#include <string>
#include <vector>

/**
 * The Callback method that is called when data is read from a curl call.
 *
 * @param data_read The data that was read from the API call
 * @param size the size of the data that was read
 * @param the number of the data that was read 
 * @param userdata A pointer that is used to move data out of the call back
 * @return 
 */
static size_t writeCallback(char *data_read, size_t size, size_t nmemb, std::string *userdata) {
  // TODO Throw exception if data_read is null 
  if(!data_read) {
    return 0;
  }
  std::size_t total_bytes(size * nmemb);
  userdata->append(data_read, total_bytes);
  return total_bytes;
}

/**
 * @brief Cleans up the curl handler and the slist used for the headers
 *
 * @param curl_handle The curl handler that is being freed
 * @param slist The slist that is being freed
 */
static void cleanup_curl(CURL *curl_handle, curl_slist *slist) {
  curl_easy_cleanup(curl_handle);

  curl_slist_free_all(slist);

  curl_global_cleanup();
}

/**
 * @brief Sets up the curl handler.
 *
 * @param curl_handle pointer to the address of the curl handler
 * @param response_code The address of the response code
 * @param api_http_link The link that the curl handler will use
 * @param json_str Pointer to where the json str will be stored.
 * @return Returns the CurlCode that was read
 */
static CURLcode setup_curl(CURL **curl_handle, long *response_code,
    const char *api_http_link, const std::basic_string<char> *json_str) {
  CURLcode resCode = CURLE_OK;
  // init the curl session 
  if(!(*curl_handle = curl_easy_init())) {
    throw new CurlInitializeFailure();
  }

  curl_global_init(CURL_GLOBAL_ALL);
  // specify URL to get 
  if((resCode = curl_easy_setopt(*curl_handle, CURLOPT_URL, api_http_link))) {
    return resCode;
  }
  // send all data to this function  
  size_t writeCallback(char *data_read, size_t size, size_t nmemb, std::string *userdata);
  if ((resCode = curl_easy_setopt(*curl_handle, CURLOPT_WRITEFUNCTION, writeCallback))) {
    return resCode;
  }
  // we pass our 'json_str' pointer to the callback function 
  if ((resCode = curl_easy_setopt(*curl_handle, CURLOPT_WRITEDATA, (void *)json_str))) {
    return resCode;
  }
  // some servers do not like requests that are made without a user-agent field, so we provide one 
  if ((resCode = curl_easy_setopt(*curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0"))) {
    return resCode;
  }
  return resCode;
}

static void setup_headers(curl_slist **slist, std::vector<std::string> headers) {
  for(std::string header : headers) {
    std::cout << header;
    curl_slist * temp_slist = curl_slist_append(*slist, header.c_str());
    if(temp_slist == NULL) {
      // TODO throw errors
    }
    *slist = temp_slist;
  }
}

ApiResponseAndJson_t CurlApiJsonFetcher::get_data(std::string api_http_link,
    std::string data,
    std::vector<std::string> header_data) {

  std::unique_ptr<std::string> json_str = std::make_unique<std::string>();
  CURL *curl_handle = NULL;
  curl_slist *slist = NULL;

  CURLcode res = CURLE_OK;
  long response_code = 0L;

  // Setup curl
  setup_curl(&curl_handle, &response_code, api_http_link.c_str(), json_str.get());
  
  // Setup headers
  setup_headers(&slist, header_data);
  
  // attempt the curl call 
  res = curl_easy_perform(curl_handle);
  
  cleanup_curl(curl_handle, slist);

  // check for errors
  if(res != CURLE_OK) {
    throw new CurlPerformFailure(res);
  }

  return {response_code, *json_str};
}

ApiResponseAndJson_t CurlApiJsonFetcher::put_data(std::string api_http_link,
    std::string data,
    std::vector<std::string> header_data) {
  std::unique_ptr<std::string> json_str = std::make_unique<std::string>();
  CURL *curl_handle;
  curl_slist *slist = NULL;
  CURLcode res;
  long response_code = 0L;


  // Setup the curl handler
  setup_curl(&curl_handle, &response_code, api_http_link.c_str(), json_str.get());

  // Setup headers
  setup_headers(&slist, header_data);

  curl_easy_setopt(curl_handle, CURLOPT_CUSTOMREQUEST, "PUT"); /* !!! */
  curl_easy_setopt(curl_handle, CURLOPT_POSTFIELDS, data.c_str()); /* data goes here */

  res = curl_easy_perform(curl_handle);

  cleanup_curl(curl_handle, slist);
  // check for errors
  if(res != CURLE_OK) {
    throw new CurlPerformFailure(res);
  }

  return {response_code, *json_str};
}

ApiResponseAndJson_t CurlApiJsonFetcher::post_data(std::string api_http_link,
    std::string data,
    std::vector<std::string> header_data) {
  std::unique_ptr<std::string> json_str = std::make_unique<std::string>();
  CURL *curl_handle;
  curl_slist *slist = NULL;
  CURLcode res;
  long response_code = 0L;

  // Setup the curl handler
  setup_curl(&curl_handle, &response_code, api_http_link.c_str(), json_str.get());

  // Setup headers
  setup_headers(&slist, header_data);

  // Setup POST data
  curl_easy_setopt(curl_handle, CURLOPT_POSTFIELDSIZE, (long)data.length());
  curl_easy_setopt(curl_handle, CURLOPT_POSTFIELDS, data.c_str());

  // attempt the curl call 
  res = curl_easy_perform(curl_handle);

  // cleanup curl stuff 
  curl_easy_cleanup(curl_handle);

  // we are done with libcurl, so clean it up
  curl_global_cleanup();

  // check for errors
  if(res != CURLE_OK) {
    throw new CurlPerformFailure(res);
  }

  return {response_code, *json_str};
}
