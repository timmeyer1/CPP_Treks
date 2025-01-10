# Application de Gestion de Treks

Cette application est conçue pour gérer une agence de voyage spécialisée dans l'organisation de treks. Elle permet de gérer les clients, les treks, les réservations et d'intégrer les informations météorologiques.

## Prérequis

### Outils de Développement

- C++ 17 ou supérieur
- CMake 3.16 ou supérieur
- Git
- Compilateur C++ (g++ recommandé)
- VSCode ou un autre IDE

### Dépendances

- Installation de MySQL library
  ```bash
  sudo apt-get install libmysqlclient-dev
  ```
- Installation de libcurl
  ```bash
  sudo apt install libcurl4-openssl-dev
  ```
- Installation de nlohmann-json
  ```bash
  sudo apt install nlohmann-json3-dev
  ```
- Qt6 (framework graphique)
  ```bash
  sudo apt-get install qt6-base-dev
  ```
- MySQL Server et bibliothèques de développement
  ```bash
  sudo apt-get install mysql-server mysql-client libmysqlclient-dev
  ```
- libcurl (pour l'API météo)
  ```bash
  sudo apt-get install libcurl4-openssl-dev
  ```

### Base de Données

1. Créer la base de données MySQL :
   ```bash
   mysql -u root -p
   CREATE DATABASE trek_manager;
   USE trek_manager;
   ```

2. Exécuter le script SQL d'initialisation :
   ```bash
   mysql -u root -p trek_manager < src/database/init_database.sql
   ```

### API Météo

1. Créer un compte sur [OpenWeatherMap](https://openweathermap.org/api).
2. Obtenir une clé API.
3. Configurer la clé dans le fichier `src/api/WeatherAPI.cpp`.

## Installation

1. Cloner le projet :
   ```bash
   git clone [url-du-projet]
   cd Treks
   ```

2. Créer le dossier de build :
   ```bash
   mkdir build
   cd build
   ```

3. Configurer et compiler :
   ```bash
   cmake ..
   make
   ```

## Démarrage de l'Application

```bash
./trek_manager
```

## Structure du Projet

```
TREKS/
├── src/
│   ├── api/           # API météo
│   ├── database/      # Gestion base de données
│   ├── models/        # Classes métier
│   ├── ui/            # Interface utilisateur
│   └── main.cpp
├── CMakeLists.txt
└── README.md
```

