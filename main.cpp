#include <iostream>
#include <fstream>
#include <string>

struct ServerConfig {
    std::string host;
    int port;
    std::string rootDirectory;
    // Ajoutez d'autres paramètres de configuration au besoin
};


ServerConfig readConfigFile(const std::string& configFile) {
    ServerConfig config;

    std::ifstream file(configFile.c_str());
    if (!file.is_open()) {
        std::cerr << "Erreur lors de l'ouverture du fichier de configuration." << std::endl;
        // Gérer l'erreur comme vous le souhaitez
        // Par exemple, quitter le programme ou retourner une configuration par défaut
        exit(EXIT_FAILURE);
    }

    std::string line;
    while (std::getline(file, line)) {
        // Analyser chaque ligne du fichier de configuration et remplir la structure
        // Par exemple, si chaque ligne est au format "clé=valeur", vous pouvez faire quelque chose comme ceci :
        // Exemple : "port=8080"
        size_t delimiterPos = line.find('=');
        if (delimiterPos != std::string::npos) {
            std::string key = line.substr(0, delimiterPos);
            std::string value = line.substr(delimiterPos + 1);

            // Remplir la structure en fonction de la clé
            if (key == "host") {
                config.host = value;
            } else if (key == "port") {
                config.port = std::stoi(value);
            } else if (key == "root_directory") {
                config.rootDirectory = value;
            }
            // Ajoutez d'autres clés et leurs valeurs correspondantes au besoin
        }
    }

    file.close();

    return config;
}


#include <iostream>
#include "server.h" // Inclure le fichier d'en-tête où se trouve la définition du serveur et la fonction de lecture du fichier de configuration

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <configuration_file>" << std::endl;
        return 1;
    }

    // Lire le fichier de configuration
    std::string configFile = argv[1];
    ServerConfig config = readConfigFile(configFile);

    // Créer et démarrer le serveur avec la configuration spécifiée
    Server server(config);
    server.run();

    return 0;
}
