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

json createJsonRpcRequest(const std::string& method, const json& params) {
    json request;
    request["jsonrpc"] = "2.0";
    request["method"] = "generateIntegers";
    request["params"] = params;
    request["id"] = 1;
    return request;
}

json sendJsonRpcRequest(const std::string& url, const json& request) {
    CURL* curl = curl_easy_init();
    std::string response;

    if (curl) {
        // Set the URL for the API endpoint
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        // Set the request headers
        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // Set the request data
        std::string requestData = request.dump();
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, requestData.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, requestData.length());

        // Set the callback function to write the response data
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);

        // Set the response data object
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        // Perform the request
        CURLcode res = curl_easy_perform(curl);

        // Check for errors
        if (res != CURLE_OK) {
            std::cerr << "cURL request failed: " << curl_easy_strerror(res) << std::endl;
        }

        // Cleanup curl handle
        curl_easy_cleanup(curl);
    }

    return json::parse(response);
}

int getBtcPrice() {
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

int getEthPrice() {
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

int getCurrentTemperature()
{
    CURL* curl;
    CURLcode res;
    std::string response;

    // Initialize the libcurl library
    curl_global_init(CURL_GLOBAL_DEFAULT);

    // Create a curl handle
    curl = curl_easy_init();
    if (curl) {
        // Set the URL for the API endpoint
        curl_easy_setopt(curl, CURLOPT_URL, "https://na_aford:P6Lmd99zMx@api.meteomatics.com/2023-05-31T00:00:00Z/t_2m:C/52.520551,13.461804/json");

        // Set the callback function to write the response data
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);

        // Set the response data object
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        // Perform the request
        res = curl_easy_perform(curl);

        // Check for errors
        if (res != CURLE_OK) {
            std::cerr << "cURL request failed: " << curl_easy_strerror(res) << std::endl;
        }
        else {
            // Parse the JSON response
            json jsonResponse = json::parse(response);

            // Extract the temperature value
            float temperature = jsonResponse["data"][0]["coordinates"][0]["dates"][0]["value"];

            // Cleanup curl handle
            curl_easy_cleanup(curl);

            // Cleanup libcurl
            curl_global_cleanup();

            // Return the temperature value as an integer
            return static_cast<int>(temperature);
        }
    }

    // Cleanup libcurl
    curl_global_cleanup();

    return -1;  // Return an error value
}

int getAtmosphere() {
    // Construct the JSON-RPC request
    json params;
    params["apiKey"] = "c54e39cd-d449-4b7a-a8d2-64f733aee93b";
    params["n"] = 1;
    params["min"] = 2;
    params["max"] = 9;
    //params["replacement"] = true;

    json request = createJsonRpcRequest("getAtmosphere", params);

    // Send the JSON-RPC request
    std::string url = "https://api.random.org/json-rpc/4/invoke";  // Replace with your JSON-RPC endpoint
    json response = sendJsonRpcRequest(url, request);

    // Print the JSON response for debugging
    //std::cout << "JSON Response: " << response << std::endl;

    // Process the JSON-RPC response
    if (response.contains("result")) {
        json result = response["result"];
        if (result.contains("random")) {
            json random = result["random"];
            if (random.contains("data")) {
                json data = random["data"];
                if (data.is_array() && !data.empty()) {
                    // Process the first value in the array
                    int atmosphere = data[0].get<int>();

                    // Print the atmosphere value
                    //std::cout << "Atmosphere: " << atmosphere << std::endl;

                    return atmosphere;
                }
                else {
                    std::cerr << "Invalid data format: Expected non-empty array" << std::endl;
                }
            }
            else {
                std::cerr << "Missing or invalid 'data' field" << std::endl;
            }
        }
        else {
            std::cerr << "Missing or invalid 'random' field" << std::endl;
        }
    }
    else if (response.contains("error")) {
        std::cerr << "JSON-RPC request failed: " << response["error"]["message"] << std::endl;
    }
    else {
        std::cerr << "Missing 'result' field" << std::endl;
    }

    return -1;  // Return an error value
}