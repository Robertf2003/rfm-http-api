#pragma once
#include "string"
#include <string>
#include <vector>
/**
 * @brief Represents the result of a curl call
 */
typedef struct {
  // The http response code of the curl call
  long https_response_code;
  // The json string received from the curl call
  std::string json_str;
} ApiResponseAndJson_t;

class IApiJsonFetcher
{
  public:
    /**
     * @brief Fetches a json from an api cal
     *
     * @param api_http_link The http link that is used for the curl call
     * @param data The data of the HTTP request
     * @param header_data A vector of header data
     * @return The result of the curl call
     */
    virtual ApiResponseAndJson_t get_data(std::string api_http_link, 
        std::string data,
        std::vector<std::string> header_data) = 0;

    virtual ApiResponseAndJson_t post_data(std::string api_http_link, 
        std::string data,
        std::vector<std::string> header_data) = 0;

    virtual ApiResponseAndJson_t put_data(std::string api_http_link, 
        std::string data,
        std::vector<std::string> header_data) = 0;

};

