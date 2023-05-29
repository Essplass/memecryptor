#include <stdio.h>
#include <curl/curl.h>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

// Callback function to write the response data into a string
size_t WriteCallback(char* data, size_t size, size_t nmemb, std::string* writerData)
{
    if (writerData == nullptr)
        return 0;

    writerData->append(data, size * nmemb);

    return size * nmemb;
}

int btc() {
    CURL* curl;
    CURLcode res;
    std::string response;

    // Initialize the libcurl library
    curl_global_init(CURL_GLOBAL_DEFAULT);

    // Create a curl handle
    curl = curl_easy_init();
    if (curl) {
        // Set the URL for the API endpoint to get the BTC price
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.coindesk.com/v1/bpi/currentprice/BTC.json");

        // Set the callback function to write the response data
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);

        // Set the response data object
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        // Perform the request
        res = curl_easy_perform(curl);

        // Check for errors
        if (res != CURLE_OK) {
            std::cerr << "cURL request failed: " << curl_easy_strerror(res) << std::endl;
            return -1;  // Return an error value
        }
        else {
            // Print the API response
           // std::cout << "BTC API response: " << response << std::endl;

            // Parse the JSON response
            json jsonResponse = json::parse(response);

            // Extract the BTC price as a float
            float btcPrice = jsonResponse["bpi"]["USD"]["rate_float"];

            // Convert the float to an integer
            int btcPriceInt = static_cast<int>(btcPrice);

            // Cleanup curl handle
            curl_easy_cleanup(curl);

            // Cleanup libcurl
            curl_global_cleanup();

            // Return the BTC price as an integer
            return btcPriceInt;
        }
    }

    // Cleanup libcurl
    curl_global_cleanup();

    return -1;  // Return an error value
}

int eth() {
    CURL* curl;
    CURLcode res;
    std::string response;

    // Initialize the libcurl library
    curl_global_init(CURL_GLOBAL_DEFAULT);

    // Create a curl handle
    curl = curl_easy_init();
    if (curl) {
        // Set the URL for the API endpoint to get the ETH price
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.coingecko.com/api/v3/simple/price?ids=ethereum&vs_currencies=usd");

        // Set the callback function to write the response data
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);

        // Set the response data object
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        // Perform the request
        res = curl_easy_perform(curl);

        // Check for errors
        if (res != CURLE_OK) {
            std::cerr << "cURL request failed: " << curl_easy_strerror(res) << std::endl;
            return -1;  // Return an error value
        }
        else {
            // Print the API response
            //std::cout << "ETH API response: " << response << std::endl;

            // Parse the JSON response
            json jsonResponse = json::parse(response);

            // Extract the ETH price as a float
            float ethPrice = jsonResponse["ethereum"]["usd"];

            // Convert the float to an integer
            int ethPriceInt = static_cast<int>(ethPrice);

            // Cleanup curl handle
            curl_easy_cleanup(curl);

            // Cleanup libcurl
            curl_global_cleanup();

            // Return the ETH price as an integer
            return ethPriceInt;
        }
    }

    // Cleanup libcurl
    curl_global_cleanup();

    return -1;  // Return an error value
}






