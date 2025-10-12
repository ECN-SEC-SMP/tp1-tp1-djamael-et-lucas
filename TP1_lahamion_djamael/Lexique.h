#ifndef LEXIQUE
#define LEXIQUE

#include <cstring>
#include <stdio.h>
#include <map>
#include <vector>
#include <iostream>
#include "utilitaire.hpp"

using namespace std;

/**
 * @brief Classe représentant un lexique, c’est-à-dire un ensemble de mots associés à un compteur d’occurrences.
 * 
 * Cette classe permet de gérer un dictionnaire de mots (sous forme de map),
 * d’y ajouter, supprimer, afficher et sauvegarder des entrées.
 */
class Lexique
{
private:
    string nom;                     // Nom du lexique
    map<string, int> mots;          // Lexique associant chaque mot à son nombre d'occurrences

public:
    /**
     * @brief Constructeur par défaut.
     * Initialise un lexique basé sur un fichier par défaut ici il s'agit du fichier "LesMiserbalesA.txt".
     */
    Lexique();

    /**
     * @brief Constructeur à partir d’un chemin de fichier.
     * Charge éventuellement un lexique depuis le fichier indiqué.
     * 
     * @param path chemin du fichier source (ex: "data/texte.txt")
     */
    Lexique(string_view path);

    /**
     * @brief Renvoie le nom du lexique.
     * @return string Nom du lexique.
     */
    string get_nom() const;

    /**
     * @brief Renvoie la map contenant les mots et leurs occurrences.
     * @return const map<string, int>& Référence constante vers la map.
     */
    const map<string, int>& get_mots() const;

    /**
     * @brief Affiche les informations générales du lexique (nom, nombre de mots, etc.)
     */
    void print();

    /**
     * @brief Sauvegarde le lexique dans un fichier.
     * 
     * @return true si la sauvegarde s’est bien déroulée, false sinon.
     */
    bool save();

    /**
     * @brief Vérifie si un mot est présent dans le lexique.
     * 
     * @param word mot à chercher.
     * @return int nombre d’occurrences du mot, ou 0 s’il est absent.
     */
    int check_word_presence(string word);

    /**
     * @brief Supprime un mot du lexique.
     * 
     * @param word mot à supprimer.
     */
    void delete_word(string word);

    /**
     * @brief Affiche le nombre de mots différents dans le lexique.
     */
    void print_number_of_words();

    /**
     * @brief Surcharge de l’opérateur << pour afficher un lexique.
     * 
     * Permet d’utiliser cout << monLexique; pour afficher directement son contenu.
     */
    friend ostream& operator<<(ostream& os, const Lexique& lex);

    /**
     * @brief Surcharge de l’opérateur +=
     * Fusionne un autre lexique dans celui-ci.
     * Les occurrences des mots communs sont additionnées.
     * 
     * @param other autre lexique à fusionner.
     */
    void operator+=(Lexique const& other);

    /**
     * @brief Surcharge de l’opérateur -=
     * Soustrait les occurrences des mots d’un autre lexique.
     * Si un mot devient nul ou négatif, il peut être supprimé.
     * 
     * @param other autre lexique à soustraire.
     */
    void operator-=(Lexique const& other);
};

/**
 * @brief Surcharge externe de l’opérateur << pour afficher un lexique.
 * 
 * @param os flux de sortie (ex: cout)
 * @param lex lexique à afficher
 * @return ostream& flux de sortie pour chaînage
 */
ostream& operator<<(ostream& os, const Lexique& lex);

#endif // LEXIQUE
