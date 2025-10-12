#include "LexiqueAvecLignes.h"
#include "utilitaire.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;
using namespace util;

/**
 * @brief Constructeur de la classe LexiqueAvecLignes.
 * 
 * Ce constructeur lit un fichier texte ligne par ligne, enregistre :
 *   - les mots dans la map héritée du Lexique (`mots`)
 *   - les numéros de ligne dans la nouvelle structure `mots_lignes`.
 * 
 * @param path chemin du fichier à analyser.
 */
LexiqueAvecLignes::LexiqueAvecLignes(string_view path) : Lexique(path) {
    ifstream fichier(path.data());  // ouverture du fichier texte
    if (!fichier) {
        cerr << "Impossible d'ouvrir " << path << endl;
        return;
    }

    string ligne;   // contiendra chaque ligne lue
    int numLigne = 1;  // compteur de lignes

    // Lecture ligne par ligne du fichier
    while (getline(fichier, ligne)) {
        // Nettoyage de la ligne : suppression de la ponctuation et mise en minuscules
        remove_punctuation(ligne);
        to_lower(ligne);

        // Découpage de la ligne en mots à l’aide d’un flux de chaînes
        istringstream iss(ligne);
        string mot;

        // Lecture de chaque mot trouvé sur la ligne
        while (iss >> mot) {
            // Ajoute le numéro de ligne à la structure mots_lignes
            mots_lignes[mot].push_back(numLigne);

            // --- Mise à jour du lexique hérité (map<string,int> mots) ---
            // get_mots() renvoie une référence constante, donc on utilise const_cast
            // pour modifier directement la map héritée du parent.
            if (!this->get_mots().count(mot)) {
                // Le mot n'existe pas encore dans la map : on l'insère avec 1 occurrence
                const_cast<map<string,int>&>(this->get_mots())[mot] = 1;
            } else {
                // Si le mot existe déjà, on incrémente le compteur
                const_cast<map<string,int>&>(this->get_mots())[mot]++;
            }
        }
        // Passage à la ligne suivante
        numLigne++;
    }
}

/**
 * @brief Retourne les numéros de lignes d'apparition d'un mot donné.
 * 
 * @param mot mot recherché.
 * @return const vector<int>& liste des numéros de lignes. Si le mot n’existe pas,
 *         retourne un vecteur vide (référence statique).
 */
const vector<int>& LexiqueAvecLignes::get_lignes(string mot) const {
    static vector<int> vide;  // vecteur vide renvoyé si le mot est absent
    auto it = mots_lignes.find(mot);
    if (it != mots_lignes.end())
        return it->second;
    return vide;
}

/**
 * @brief Affiche le lexique complet avec, pour chaque mot :
 *        - le nombre d’occurrences
 *        - les numéros de lignes où il apparaît
 */
void LexiqueAvecLignes::print() {
    cout << "Lexique avec lignes : " << get_nom() << endl;

    // Parcours de chaque mot du lexique
    for (auto& entry : mots_lignes) {
        cout << entry.first << " (" << entry.second.size()
             << " occurrences, lignes: ";

        // Affiche les numéros de lignes séparés par des virgules
        for (size_t i = 0; i < entry.second.size(); ++i) {
            cout << entry.second[i];
            if (i < entry.second.size() - 1)
                cout << ", ";
        }
        cout << ")" << endl;
    }
}
