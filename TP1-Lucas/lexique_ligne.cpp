/* Class Lexique_her */

#include <iostream>
#include "lexique.h"
#include "lexique_ligne.h"
#include "utilitaire.hpp"
#include <math.h>  
#include <fstream> 
#include <map>
#include <sstream>

using namespace std;

//constructeur sans parametre
Lexique_ligne::Lexique_ligne() : Lexique() {
    LignesParMot = map<string, vector<int>>(); //initialise la map
}

//Méthode pour construire le lexique avec lignes
void Lexique_ligne::ConstruireLexiqueAvecLignes(const string& nomFichier) {
    //Ouvre le fichier en lecture
    ifstream fichierEntree("tp1-Lexique-output/Lexique-" + Nom + "-output.txt");  //permet de lire le fichier d'entrée
    if (!fichierEntree.is_open()) {
        cerr << "Erreur lors de l'ouverture du fichier de sortie : " << nomFichier << endl;
        return;
    }

    string ligne;
    int numeroLigne = 0; //compteur de lignes

    while (getline(fichierEntree, ligne)) { //tant que il y a des lignes à lire
        numeroLigne++; //incrémente le numéro de ligne
        istringstream iss(ligne); //permet de lire chaque mot de la ligne
        string word; //variable pour stocker chaque mot
        while (iss >> word) {  //tant que il y a des mots à lire
            // Nettoyer le mot en supprimant la ponctuation et en le mettant en minuscules
            util::remove_punctuation(word);
            util::to_lower(word);
            if (!word.empty()) {    //si le mot n'est pas vide
                LignesParMot[word].push_back(numeroLigne); //alors on ajoute le numéro de ligne à la liste des lignes pour ce mot
            }
        }
    }

    fichierEntree.close();
}

//Méthode pour obtenir les lignes pour un mot donné
vector<int> Lexique_ligne::getLignesPourMot(const string& mot) const {
    string motNettoye = mot; //copie du mot à tester
    util::remove_punctuation(motNettoye); //supprime la ponctuation
    util::to_lower(motNettoye); //met en minuscules

    auto it = LignesParMot.find(motNettoye); //cherche le mot dans la map
    if (it != LignesParMot.end()) { //si le mot est trouvé
        return it->second; //retourne la liste des lignes
    } else {
        return vector<int>(); //retourne une liste vide si le mot n'est pas trouvé
    }
}