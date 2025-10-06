#pragma once

#include <iostream>


#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>

using namespace std;

/**
 * @brief Classe Lexique
 * 
 * Objectif : Gérer un lexique de mots et leurs occurrences
 * 
 * Attributs :
 * - nom : nom du lexique
 * - occurrences : nombre d'occurrences des mots dans le lexique
 * 
 * Methodes :
 * sauvegarderLexique : sauvegarder le lexique dans un fichier
 * testerMot : tester la présence d'un mot et retourner son nombre d'occurrences
 * supprimerMot : supprimer un mot du lexique
 * nombreMotsDifferents : afficher le nombre de mots différents dans le lexique
 * 
 */

class Lexique{
private:
    string Nom;
    int Nbr_occurences;          

public:

    //constructeur sans parametre
    Lexique();

    //Accesseur Nom
    string GetNom() const;

    //Accesseur Nbr_occurences
    int GetNbr_occurences() const;

    //Mutateur Nom
    void SetNom(string nom);

    //Mutateur Nbr_occurences
    void SetNbr_occurences(int nbr);



    //Méthode pour sauvegarder le contenu du lexique produit dans un fichier
    void sauvegarderLexique(const string& nomFichier) const;

    
    //Méthode tester la présence d'un mot dans le lexique et retourner son nombre d'occurrences
    int testerMot(const string& mot) const;

    ///Méthode pour supprimer un mot du lexique
    void supprimerMot(const string& mot);

    //Méthode pour afficher le nombre de mots différents dans le lexique
    int nombreMotsDifferents() const;
};




