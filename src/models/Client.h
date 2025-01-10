#pragma once
#include <string>

class Client {
private:
    int id;
    std::string nom;
    std::string prenom;
    std::string email;
    std::string telephone;
    std::string dateInscription;

public:
    Client(const std::string& nom, const std::string& prenom, 
           const std::string& email, const std::string& telephone);
    
    // Getters
    int getId() const { return id; }
    std::string getNom() const { return nom; }
    std::string getPrenom() const { return prenom; }
    std::string getEmail() const { return email; }
    std::string getTelephone() const { return telephone; }
    std::string getDateInscription() const { return dateInscription; }
    
    // Setters
    void setId(int newId) { id = newId; }
    void setNom(const std::string& newNom) { nom = newNom; }
    void setPrenom(const std::string& newPrenom) { prenom = newPrenom; }
    void setEmail(const std::string& newEmail) { email = newEmail; }
    void setTelephone(const std::string& newTel) { telephone = newTel; }
};
