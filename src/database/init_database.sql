CREATE DATABASE trek_manager;
USE trek_manager;

CREATE TABLE clients (
    id INT PRIMARY KEY AUTO_INCREMENT,
    nom VARCHAR(100) NOT NULL,
    prenom VARCHAR(100) NOT NULL,
    email VARCHAR(255) UNIQUE NOT NULL,
    telephone VARCHAR(20) NOT NULL,
    date_inscription DATETIME DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE treks (
    id INT PRIMARY KEY AUTO_INCREMENT,
    nom VARCHAR(255) NOT NULL,
    lieu VARCHAR(255) NOT NULL,
    duree INT NOT NULL,
    prix DECIMAL(10,2) NOT NULL,
    niveau VARCHAR(50) NOT NULL,
    description TEXT
);

CREATE TABLE reservations (
    id INT PRIMARY KEY AUTO_INCREMENT,
    client_id INT NOT NULL,
    trek_id INT NOT NULL,
    date_reservation DATETIME DEFAULT CURRENT_TIMESTAMP,
    statut VARCHAR(50) DEFAULT 'En attente',
    FOREIGN KEY (client_id) REFERENCES clients(id),
    FOREIGN KEY (trek_id) REFERENCES treks(id)
);
