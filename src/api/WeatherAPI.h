#pragma once
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

class WeatherAPI {
private:
    std::string apiKey;
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp);
    std::string makeRequest(const std::string& url);

public:
    WeatherAPI(const std::string& key);
    ~WeatherAPI();
    
    struct WeatherData {
        double temperature;
        int humidity;
        std::string description;
        double windSpeed;
    };

    WeatherData getWeatherByCoordinates(double lat, double lon);
};
