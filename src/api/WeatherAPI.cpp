#include "WeatherAPI.h"
#include <stdexcept>

WeatherAPI::WeatherAPI(const std::string& key) : apiKey("e3e294b9ac2fb825df5b97f6c895bcde") {
    curl_global_init(CURL_GLOBAL_DEFAULT);
}
WeatherAPI::~WeatherAPI() {
    curl_global_cleanup();
}

size_t WeatherAPI::WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp) {
    userp->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string WeatherAPI::makeRequest(const std::string& url) {
    CURL* curl = curl_easy_init();
    std::string readBuffer;

    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        CURLcode res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        if(res != CURLE_OK) {
            throw std::runtime_error("Erreur lors de la requête curl");
        }
    }

    return readBuffer;
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

