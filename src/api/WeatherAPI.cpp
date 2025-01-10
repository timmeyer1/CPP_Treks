#include "WeatherAPI.h"

WeatherAPI::WeatherAPI(const std::string& key) : apiKey(key) {
    curl_global_init(CURL_GLOBAL_DEFAULT);
}

WeatherAPI::~WeatherAPI() {
    curl_global_cleanup();
}

size_t WeatherAPI::WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp) {
    userp->append((char*)contents, size * nmemb);
    return size * nmemb;
}

WeatherAPI::WeatherData WeatherAPI::getWeatherByCoordinates(double lat, double lon) {
    std::string url = "https://api.openweathermap.org/data/2.5/weather?lat=" + 
                      std::to_string(lat) + "&lon=" + std::to_string(lon) + 
                      "&units=metric&appid=" + apiKey;
    
    std::string response = makeRequest(url);
    auto json = nlohmann::json::parse(response);
    
    WeatherData data;
    data.temperature = json["main"]["temp"];
    data.humidity = json["main"]["humidity"];
    data.description = json["weather"][0]["description"];
    data.windSpeed = json["wind"]["speed"];
    
    return data;
}
