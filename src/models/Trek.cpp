#include "Trek.h"

Trek::Trek(const std::string& nom, const std::string& lieu, int duree,
           double prix, const std::string& niveau, const std::string& description)
    : nom(nom), lieu(lieu), duree(duree), prix(prix), 
      niveau(niveau), description(description) {}
