#include "DatabaseManager.h"
#include <stdexcept>

DatabaseManager* DatabaseManager::instance = nullptr;

DatabaseManager::DatabaseManager() {
    if (!connect()) {
        throw std::runtime_error("Échec de connexion à la base de données");
    }
}

bool DatabaseManager::connect() {
    connection = mysql_init(nullptr);
    if (!connection) {
        return false;
    }

    if (!mysql_real_connect(connection, "localhost", "user", "password",
                           "trek_manager", 0, nullptr, 0)) {
        return false;
    }
    return true;
}

DatabaseManager* DatabaseManager::getInstance() {
    if (instance == nullptr) {
        instance = new DatabaseManager();
    }
    return instance;
}

DatabaseManager::~DatabaseManager() {
    if (connection) {
        mysql_close(connection);
    }
}

// Implémentation des méthodes CRUD pour Client
bool DatabaseManager::addClient(Client& client) {
    std::string query = "INSERT INTO clients (nom, prenom, email, telephone) "
                       "VALUES ('" + client.getNom() + "', '" + 
                       client.getPrenom() + "', '" +
                       client.getEmail() + "', '" + 
                       client.getTelephone() + "')";
    
    return mysql_query(connection, query.c_str()) == 0;
}
