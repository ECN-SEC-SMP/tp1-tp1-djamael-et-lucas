#ifndef LEXIQUE_AVEC_LIGNES_H
#define LEXIQUE_AVEC_LIGNES_H

#include "Lexique.h"
#include <map>
#include <vector>
#include <string>

using namespace std;

/**
 * @brief Classe dérivée de Lexique, qui associe à chaque mot
 *        la liste des lignes dans lesquelles il apparaît.
 * 
 * Cette classe permet d’analyser un texte non seulement en comptant
 * les occurrences des mots (hérité de Lexique),
 * mais aussi en enregistrant les numéros de lignes où chaque mot apparaît.
 */
class LexiqueAvecLignes : public Lexique {
private:
    /**
     * @brief Conteneur associant chaque mot à la liste des lignes où il apparaît.
     * 
     * Exemple :
     * "bonjour" -> {1, 5, 8}
     */
    map<string, vector<int>> mots_lignes;

public:
    /**
     * @brief Construit un lexique à partir d’un fichier texte.
     * 
     * Lit le fichier ligne par ligne, enregistre les mots et les lignes
     * d’apparition pour chacun d’eux.
     * 
     * @param path chemin du fichier texte à analyser.
     */
    LexiqueAvecLignes(string_view path);

    /**
     * @brief Retourne la liste des numéros de lignes où apparaît un mot donné.
     * 
     * @param mot mot recherché.
     * @return const vector<int>& référence constante vers le vecteur de lignes.
     * 
     * @note Si le mot n’existe pas dans le lexique, cette fonction peut lever
     * une exception (out_of_range). Il est recommandé de vérifier la présence du mot avant.
     */
    const vector<int>& get_lignes(string mot) const;

    /**
     * @brief Affiche le contenu complet du lexique, avec les numéros de lignes
     *        d’apparition pour chaque mot.
     * 
     * Exemple d’affichage :
     * 
     * ```
     * Mot        Occurrences   Lignes
     * maison     3             [1, 2, 10]
     * chat       2             [4, 8]
     * ```
     */
    void print();
};

#endif // LEXIQUE_AVEC_LIGNES_H
