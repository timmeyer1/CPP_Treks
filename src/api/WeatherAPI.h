#pragma once
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

class WeatherAPI {
public:
    struct WeatherData {
        double temperature;
        int humidity;
        std::string description;
        double windSpeed;
    };

    WeatherAPI(const std::string& apiKey);
    ~WeatherAPI();
    
    WeatherData getWeatherByCoordinates(double lat, double lon);

private:
    std::string apiKey;
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp);
    std::string makeRequest(const std::string& url);
};
