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
    ifstream fichierEntree("tp1-Lexique-input/" + nomFichier); //permet de lire le fichier d'entrée
    if (!fichierEntree.is_open()) {
        cerr << "Erreur lors de l'ouverture du fichier d'entrée : " << nomFichier << endl;
        return;
    }

    //Crée le nom du fichier de sortie
    string nomFichierSortie = "tp1-Lexique-output/Lexique-Lucas-output.txt";

    //Ouvre le fichier en écriture
    ofstream fichierSortie(nomFichierSortie); //permet de créer et écrire dans le fichier de sortie
    if (!fichierSortie.is_open()) {
        cerr << "Erreur lors de la creation du fichier de sortie : " << nomFichierSortie << endl;
        return;
    }

    //Copie le contenu du fichier d'entrée vers le fichier de sortie
    string ligne;
    while (getline(fichierEntree, ligne)) { //tant que il y a des lignes à lire
        fichierSortie << ligne << endl;     // alors on écrit la ligne dans le fichier de sortie
    }

    //Ferme les fichiers
    fichierEntree.close();
    fichierSortie.close();

    cout << "Le lexique a ete sauvegarde dans le fichier : " << nomFichierSortie << endl;
}

//Méthode tester la présence d'un mot dans le lexique de sortie et retourner son nombre d'occurrences
int Lexique::testerMot(const string& mot) const{
    //Ouvre le fichier en lecture
    ifstream fichierEntree("tp1-Lexique-output/Lexique-Lucas-output.txt"); //permet de lire le fichier de sortie
    if (!fichierEntree.is_open()) {
        cerr << "Erreur lors de l'ouverture du fichier de sortie : " << Nom << endl;
        return 0;
    }

    //Utilisation d'une map pour stocker les occurrences des mots
    map<string, int> occurrences;           //map qui associe chaque mot à son nombre d'occurrences
    string ligne;
    while (getline(fichierEntree, ligne)) { //tant que il y a des lignes à lire
        istringstream iss(ligne);           //permet de lire chaque mot de la ligne
        string word;                        //variable pour stocker chaque mot
        while (iss >> word) {               //tant que il y a des mots à lire
            // Nettoyer le mot en supprimant la ponctuation et en le mettant en minuscules
            util::remove_punctuation(word);
            util::to_lower(word);
            if (!word.empty()) {     //si le mot n'est pas vide
                occurrences[word]++; //alors on incrémente son nombre d'occurrences dans la map
            }
        }
    }

    //Ferme le fichier
    fichierEntree.close();

    // Recherche du mot demandé
    string motNettoye = mot;
    util::remove_punctuation(motNettoye);
    util::to_lower(motNettoye);

    auto it = occurrences.find(motNettoye); //cherche le mot dans la map
    if (it != occurrences.end()) {          //si le mot est trouvé
        return it->second;                  // Retourne le nombre d'occurrences du mot
    } else {
        return 0; // Mot non trouvé
    }
}

//Méthode pour supprimer un mot du lexique
void Lexique::supprimerMot(const std::string& mot) {
    std::ifstream fichierEntree("tp1-Lexique-output/Lexique-Lucas-output.txt"); //permet de lire le fichier de sortie
    if (!fichierEntree.is_open()) {
        std::cerr << "Erreur lors de l'ouverture du fichier d'entree : " << Nom << std::endl;
        return;
    }

    std::ostringstream nouveauTexte; //flux pour stocker le nouveau contenu du fichier sans le mot à supprimer
    std::string motNettoye = mot;    //nettoie le mot à supprimer
    util::remove_punctuation(motNettoye);
    util::to_lower(motNettoye);

    std::string ligne; //variable pour stocker chaque ligne lue
    bool motSupprime = false; //indique si le mot a été supprimé

    while (std::getline(fichierEntree, ligne)) { //tant que il y a des lignes à lire
        std::istringstream iss(ligne); //permet de lire chaque mot de la ligne
        std::ostringstream ligneFiltree; //flux pour stocker la ligne sans le mot à supprimer
        std::string motActuel; //variable pour stocker chaque mot
        bool premierMot = true; //indique si c'est le premier mot de la ligne

        while (iss >> motActuel) { //tant que il y a des mots à lire
            std::string motTest = motActuel; //copie du mot actuel pour le tester
            util::remove_punctuation(motTest);
            util::to_lower(motTest);

            if (motTest == motNettoye) { //si le mot actuel est celui à supprimer
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

    fichierSortie << nouveauTexte.str(); // écrit le nouveau contenu dans le fichier
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
    map<string, int> occurrences;          //map qui associe chaque mot à son nombre d'occurrences
    string ligne;
    while (getline(fichierEntree, ligne)) { //tant que il y a des lignes à lire
        istringstream iss(ligne);
        string word;
        while (iss >> word) {  //tant que il y a des mots à lire
            // Nettoyer le mot en supprimant la ponctuation et en le mettant en minuscules
            util::remove_punctuation(word);
            util::to_lower(word);
            if (!word.empty()) {    //si le mot n'est pas vide
                occurrences[word]++; //alors on incrémente son nombre d'occurrences dans la map 
            }
        }
    }

    //Ferme le fichier
    fichierEntree.close();

    //Retourne le nombre de mots différents
    return occurrences.size();
}