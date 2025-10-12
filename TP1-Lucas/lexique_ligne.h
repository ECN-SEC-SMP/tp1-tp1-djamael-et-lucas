#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include "lexique.h"


using namespace std;

/**
 * @brief Classe Lexique_ligne
 * 
 * Objectif : Vous créerez ensuite un lexique qui héritera de votre première classe, lexique mais qui permet
 * de garder en plus pour chaque mot du lexique la ligne du fichier où il a été rencontré.
 * 
 * Attributs :
 * - LignesParMot : un map associant chaque mot à la liste des lignes où il apparaît
 *
 * Methodes :
 * ConstruireLexiqueAvecLignes : Méthode pour construire le lexique avec lignes
 * getLignesPourMot : Méthode pour obtenir les lignes pour un mot donné
 * 
 */

class Lexique_ligne : public Lexique{ //heritage de la classe Lexique
private:
    map<string, vector<int>> LignesParMot; //map qui associe chaque mot à la liste des lignes où il apparaît

public:

    //constructeur sans parametre
    Lexique_ligne();
    
    //Méthode pour construire le lexique avec lignes
    void ConstruireLexiqueAvecLignes(const string& nomFichier);

    //Méthode pour obtenir les lignes pour un mot donné
    vector<int> getLignesPourMot(const string& mot) const;
};