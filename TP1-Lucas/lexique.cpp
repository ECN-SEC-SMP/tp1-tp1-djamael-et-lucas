/* Class lexique */

//#include <stdio.h>
#include <iostream>
#include "lexique.h"
#include "utilitaire.hpp"
#include <math.h>  
#include <fstream> 
#include <map>
#include <sstream>
#include <set>

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
void Lexique::sauvegarderLexique(const string& nomFichier) const {
    ifstream fichierEntree("tp1-Lexique-input/" + nomFichier);
    if (!fichierEntree.is_open()) {
        cerr << "Erreur lors de l'ouverture du fichier d'entrée : " << nomFichier << endl;
        return;
    }

    string nomFichierSortie = "tp1-Lexique-output/Lexique-" + Nom + "-output.txt";
    ofstream fichierSortie(nomFichierSortie);
    if (!fichierSortie.is_open()) {
        cerr << "Erreur lors de la creation du fichier de sortie : " << nomFichierSortie << endl;
        return;
    }

    string ligne, mot;
    while (getline(fichierEntree, ligne)) {
        istringstream iss(ligne);
        while (iss >> mot) {
            util::remove_punctuation(mot);
            util::to_lower(mot);
            if (!mot.empty())
                fichierSortie << mot << "\n";
        }
    }

    fichierEntree.close();
    fichierSortie.close();
    cout << "Le lexique a ete sauvegarde dans : " << nomFichierSortie << endl;
}



//Méthode tester la présence d'un mot dans le lexique de sortie et retourner son nombre d'occurrences
int Lexique::testerMot(const string& mot) const{
    //Ouvre le fichier en lecture
    ifstream fichierEntree("tp1-Lexique-output/Lexique-" + Nom + "-output.txt"); //permet de lire le fichier de sortie
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
    std::ifstream fichierEntree("tp1-Lexique-output/Lexique-" + Nom + "-output.txt"); //permet de lire le fichier de sortie
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
    std::ofstream fichierSortie("tp1-Lexique-output/Lexique-" + Nom + "-output.txt", std::ios::trunc);
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
    ifstream fichierEntree("tp1-Lexique-output/Lexique-" + Nom + "-output.txt");
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

// -----------------------------------------------------------------------------

// Surcharge de l'opérateur <<
ostream& operator<<(ostream& os, const Lexique& lex) {
    ifstream fichierEntree("tp1-Lexique-output/Lexique-" + lex.GetNom() + "-output.txt");
    if (!fichierEntree.is_open()) {
        os << "Erreur : impossible d'ouvrir le fichier du lexique." << endl;
        return os;
    }

    map<string, int> occurrences;
    string ligne;

    while (getline(fichierEntree, ligne)) {
        istringstream iss(ligne);
        string word;
        while (iss >> word) {
            util::remove_punctuation(word);
            util::to_lower(word);
            if (!word.empty()) {
                occurrences[word]++;
            }
        }
    }

    fichierEntree.close();

    os << "=== Contenu du lexique : " << lex.GetNom() << " ===" << endl;
    for (const auto& [mot, nb] : occurrences) {
        os << mot << " : " << nb << endl;
    }
    os << "Nombre total de mots differents : " << occurrences.size() << endl;

    return os;
}



// Surcharge += : fusionner deux lexiques
Lexique& Lexique::operator+=(const Lexique& autre) {
    string fichier1 = "tp1-Lexique-output/Lexique-" + Nom + "-output.txt";
    string fichier2 = "tp1-Lexique-output/Lexique-" + autre.GetNom() + "-output.txt";

    ifstream in1(fichier1);
    ifstream in2(fichier2);

    if (!in1.is_open() || !in2.is_open()) {
        cerr << "Erreur : impossible d'ouvrir un des fichiers pour la fusion." << endl;
        return *this;
    }

    // Map pour stocker les occurrences fusionnées
    map<string, int> occurrences;
    auto lireFichier = [&](ifstream& in) {
        string ligne, mot;
        while (getline(in, ligne)) {
            istringstream iss(ligne);
            while (iss >> mot) {
                util::remove_punctuation(mot);
                util::to_lower(mot);
                if (!mot.empty()) occurrences[mot]++;
            }
        }
    };

    lireFichier(in1);
    lireFichier(in2);
    in1.close();
    in2.close();

    // Réécrire le fichier fusionné dans le fichier du premier lexique
    ofstream out(fichier1, ios::trunc);
    if (!out.is_open()) {
        cerr << "Erreur lors de l'écriture du fichier fusionné." << endl;
        return *this;
    }

    for (auto& [mot, count] : occurrences) {
        out << mot << " (" << count << ")\n";
    }

    out.close();

    cout << "Fusion terminee : " << fichier1 << " contient maintenant la fusion de "
         << Nom << " et " << autre.GetNom() << endl;

    return *this;
}

// Surcharge -= : différence entre deux lexiques

Lexique& Lexique::operator-=(const Lexique& autre) {
    string fichier1 = "tp1-Lexique-output/Lexique-" + Nom + "-output.txt";
    string fichier2 = "tp1-Lexique-output/Lexique-" + autre.GetNom() + "-output.txt";

    ifstream in1(fichier1);
    ifstream in2(fichier2);

    if (!in1.is_open() || !in2.is_open()) {
        cerr << "Erreur : impossible d'ouvrir les fichiers pour la différence." << endl;
        return *this;
    }

    // Charger tous les mots du second lexique
    set<string> motsASupprimer;
    string ligne, mot;
    while (getline(in2, ligne)) {
        istringstream iss(ligne);
        while (iss >> mot) {
            util::remove_punctuation(mot);
            util::to_lower(mot);
            if (!mot.empty())
                motsASupprimer.insert(mot);
        }
    }

    // Lire le premier lexique et ne garder que les mots absents du second
    set<string> motsResultats;
    while (getline(in1, ligne)) {
        istringstream iss(ligne);
        while (iss >> mot) {
            util::remove_punctuation(mot);
            util::to_lower(mot);
            if (!mot.empty() && motsASupprimer.find(mot) == motsASupprimer.end())
                motsResultats.insert(mot);
        }
    }

    in1.close();
    in2.close();

    // Réécrire le fichier du premier lexique avec les mots filtrés
    ofstream out(fichier1, ios::trunc);
    if (!out.is_open()) {
        cerr << "Erreur lors de la réécriture du fichier de sortie : " << fichier1 << endl;
        return *this;
    }

    for (const auto& m : motsResultats)
        out << m << "\n";

    out.close();

    cout << "Différence terminée : " << fichier1
         << " ne contient plus les mots présents dans "
         << autre.GetNom() << endl;

    return *this;
}