/**
 * @file curl-api-json-fetcher.hpp
 * @brief Curl style implementation of the api-json-fetcher
 */

#pragma once
#include "api-json-fetch.hpp"
#include <curl/curl.h>
class CurlApiJsonFetcher: public IApiJsonFetcher {
  public:
    ApiResponseAndJson_t get_data(std::string api_http_link, 
        std::string data,
        std::vector<std::string> header_data);

    ApiResponseAndJson_t post_data(std::string api_http_link, 
        std::string data,
        std::vector<std::string> header_data);

    ApiResponseAndJson_t put_data(std::string api_http_link, 
        std::string data,
        std::vector<std::string> header_data);
};
