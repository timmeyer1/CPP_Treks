#include "Client.h"
#include <ctime>

Client::Client(const std::string& nom, const std::string& prenom, 
               const std::string& email, const std::string& telephone)
    : nom(nom), prenom(prenom), email(email), telephone(telephone) {
    time_t now = time(nullptr);
    dateInscription = ctime(&now);
}
