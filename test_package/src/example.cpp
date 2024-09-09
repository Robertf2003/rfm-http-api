#include "curl-api-json-fetcher.hpp"
#include <vector>
#include <string>

int main() {
    CurlApiJsonFetcher apiJsonFetcher = CurlApiJsonFetcher();

    std::vector<std::string> header_data = std::vector<std::string>();
    apiJsonFetcher.get_data("https://example.com", "", header_data);
}
