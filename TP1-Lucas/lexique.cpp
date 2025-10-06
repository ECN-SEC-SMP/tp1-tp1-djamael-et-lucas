/* Class lexique */

//#include <stdio.h>
#include <iostream>
#include "lexique.h"
#include "utilitaire.hpp"
#include <math.h>  
#include <fstream> 
#include <map>
#include <sstream>


using namespace std;

//constructeur sans parametre
Lexique::Lexique(){
    Nom = "Lexique";
    Nbr_occurences = 0;
}

//Accesseur Nom
string Lexique::GetNom() const{
    return Nom;
}

//Accesseur Nbr_occurences
int Lexique::GetNbr_occurences() const{
    return Nbr_occurences;
}

//Mutateur Nom
void Lexique::SetNom(string nom){
    Nom = nom;
}

//Mutateur Nbr_occurences
void Lexique::SetNbr_occurences(int nbr){
    Nbr_occurences = nbr;
}

/*------------------------------------------------------------------------------------*/
/* Liste des méthodes de gestion du lexique */
/*------------------------------------------------------------------------------------*/

//Méthode pour sauvegarder le contenu du lexique produit dans un fichier
void Lexique::sauvegarderLexique(const string& nomFichier) const{
    //Ouvre le fichier en lecture
    ifstream fichierEntree("tp1-Lexique-input/" + nomFichier);
    if (!fichierEntree.is_open()) {
        cerr << "Erreur lors de l'ouverture du fichier d'entrée : " << nomFichier << endl;
        return;
    }

    //Crée le nom du fichier de sortie
    string nomFichierSortie = "tp1-Lexique-output/Lexique-Lucas-output.txt";

    //Ouvre le fichier en écriture
    ofstream fichierSortie(nomFichierSortie);
    if (!fichierSortie.is_open()) {
        cerr << "Erreur lors de la creation du fichier de sortie : " << nomFichierSortie << endl;
        return;
    }

    //Copie le contenu du fichier d'entrée vers le fichier de sortie
    string ligne;
    while (getline(fichierEntree, ligne)) {
        fichierSortie << ligne << endl;
    }

    //Ferme les fichiers
    fichierEntree.close();
    fichierSortie.close();

    cout << "Le lexique a ete sauvegarde dans le fichier : " << nomFichierSortie << endl;
}

//Méthode tester la présence d'un mot dans le lexique de sortie et retourner son nombre d'occurrences
int Lexique::testerMot(const string& mot) const{
    //Ouvre le fichier en lecture
    ifstream fichierEntree("tp1-Lexique-output/Lexique-Lucas-output.txt");
    if (!fichierEntree.is_open()) {
        cerr << "Erreur lors de l'ouverture du fichier de sortie : " << Nom << endl;
        return 0;
    }

    //Utilisation d'une map pour stocker les occurrences des mots
    map<string, int> occurrences;
    string ligne;
    while (getline(fichierEntree, ligne)) {
        istringstream iss(ligne);
        string word;
        while (iss >> word) {
            // Nettoyer le mot en supprimant la ponctuation et en le mettant en minuscules
            util::remove_punctuation(word);
            util::to_lower(word);
            if (!word.empty()) {
                occurrences[word]++;
            }
        }
    }

    //Ferme le fichier
    fichierEntree.close();

    // Recherche du mot demandé
    string motNettoye = mot;
    util::remove_punctuation(motNettoye);
    util::to_lower(motNettoye);

    auto it = occurrences.find(motNettoye);
    if (it != occurrences.end()) {
        return it->second; // Retourne le nombre d'occurrences du mot
    } else {
        return 0; // Mot non trouvé
    }
}

//Méthode pour supprimer un mot du lexique
void Lexique::supprimerMot(const std::string& mot) {
    std::ifstream fichierEntree("tp1-Lexique-output/Lexique-Lucas-output.txt");
    if (!fichierEntree.is_open()) {
        std::cerr << "Erreur lors de l'ouverture du fichier d'entree : " << Nom << std::endl;
        return;
    }

    std::ostringstream nouveauTexte;
    std::string motNettoye = mot;
    util::remove_punctuation(motNettoye);
    util::to_lower(motNettoye);

    std::string ligne;
    bool motSupprime = false;

    while (std::getline(fichierEntree, ligne)) {
        std::istringstream iss(ligne);
        std::ostringstream ligneFiltree;
        std::string motActuel;
        bool premierMot = true;

        while (iss >> motActuel) {
            std::string motTest = motActuel;
            util::remove_punctuation(motTest);
            util::to_lower(motTest);

            if (motTest == motNettoye) {
                motSupprime = true;
                continue; // on ne réécrit pas ce mot
            }

            if (!premierMot) ligneFiltree << " ";
            ligneFiltree << motActuel;
            premierMot = false;
        }

        nouveauTexte << ligneFiltree.str() << "\n";
    }

    fichierEntree.close();

    if (!motSupprime) {
        std::cout << "Le mot <" << mot << "> n'est pas present dans le lexique." << std::endl;
        return;
    }

    // Réécriture du fichier
    std::ofstream fichierSortie("tp1-Lexique-output/Lexique-Lucas-output.txt", std::ios::trunc);
    if (!fichierSortie.is_open()) {
        std::cerr << "Erreur lors de la creation du fichier de sortie : " << Nom << std::endl;
        return;
    }

    fichierSortie << nouveauTexte.str();
    fichierSortie.close();

    std::cout << "Le mot <" << mot << "> a ete supprime du lexique." << std::endl;
}

//Méthode pour afficher le nombre de mots différents dans le lexique
int Lexique::nombreMotsDifferents() const{
    //Ouvre le fichier en lecture
    ifstream fichierEntree("tp1-Lexique-output/Lexique-Lucas-output.txt");
    if (!fichierEntree.is_open()) {
        cerr << "Erreur lors de l'ouverture du fichier de sortie : " << Nom << endl;
        return 0;
    }

    //Utilisation d'une map pour stocker les occurrences des mots
    map<string, int> occurrences;
    string ligne;
    while (getline(fichierEntree, ligne)) {
        istringstream iss(ligne);
        string word;
        while (iss >> word) {
            // Nettoyer le mot en supprimant la ponctuation et en le mettant en minuscules
            util::remove_punctuation(word);
            util::to_lower(word);
            if (!word.empty()) {
                occurrences[word]++;
            }
        }
    }

    //Ferme le fichier
    fichierEntree.close();

    //Retourne le nombre de mots différents
    return occurrences.size();
}