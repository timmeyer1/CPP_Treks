#pragma once
#include <string>

class Trek {
private:
    int id;
    std::string nom;
    std::string lieu;
    int duree;
    double prix;
    std::string niveau;
    std::string description;

public:
    Trek(const std::string& nom, const std::string& lieu, int duree, 
         double prix, const std::string& niveau, const std::string& description);

    // Getters
    int getId() const { return id; }
    std::string getNom() const { return nom; }
    std::string getLieu() const { return lieu; }
    int getDuree() const { return duree; }
    double getPrix() const { return prix; }
    std::string getNiveau() const { return niveau; }
    std::string getDescription() const { return description; }

    // Setters
    void setId(int newId) { id = newId; }
    void setNom(const std::string& newNom) { nom = newNom; }
    void setLieu(const std::string& newLieu) { lieu = newLieu; }
    void setDuree(int newDuree) { duree = newDuree; }
    void setPrix(double newPrix) { prix = newPrix; }
    void setNiveau(const std::string& newNiveau) { niveau = newNiveau; }
    void setDescription(const std::string& newDesc) { description = newDesc; }
};
