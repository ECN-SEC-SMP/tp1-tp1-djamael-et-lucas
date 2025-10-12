#include "Lexique.h"
#include "utilitaire.hpp"
#include <fstream>

using namespace util;

// Nom par défaut du lexique s’il n’est pas défini
#define DEFAULT_NAME "Le_lexique"

// Délimiteurs utilisés pour découper le texte en mots
const char* delimeters = " \r\n\t";

/**
 * @brief Constructeur par défaut du lexique.
 * Charge par défaut le contenu du fichier "lesMiserables_A.txt" 
 * et construit la map de mots avec leur fréquence d’apparition.
 */
Lexique::Lexique()
{
    string content;
    string the_name;
    string_view path = "lesMiserables_A.txt";
    char* pch;

    // Détermination du nom du lexique à partir du nom de fichier (sans extension)
    size_t pos = path.find('.');
    if (pos != string::npos)
        the_name = path.substr(0, pos);
    else
        the_name = DEFAULT_NAME;

    this->nom = the_name;

    // Lecture du contenu du fichier dans la chaîne 'content'
    (void)readFileIntoString(path, content);
    
    // Nettoyage du contenu : suppression ponctuation et conversion en minuscules
    remove_punctuation(content);
    to_lower(content);

    // Copie du contenu dans un buffer modifiable pour strtok()
    char* buffer = new char[content.size() + 1];
    strcpy(buffer, content.c_str());

    // Découpage de la chaîne en mots selon les délimiteurs
    pch = strtok(buffer, delimeters);

    while (pch != NULL)
    {
        // Si le mot n’est pas encore présent dans la map
        if (!this->mots.count(pch))
        {
            // Ajout avec valeur initiale 1
            this->mots.insert(pair<string, int>(pch, 1));
        }
        else
        {
            // Incrémentation du compteur si le mot existe déjà
            this->mots[pch]++;
        }

        // Passage au mot suivant
        pch = strtok(NULL, delimeters);
    }

    // Libération de la mémoire allouée dynamiquement
    delete[] buffer;
}

/**
 * @brief Constructeur du lexique à partir d’un fichier spécifié.
 * 
 * @param path chemin du fichier à charger
 */
Lexique::Lexique(string_view path)
{
    string content;
    string the_name;
    char* pch;

    // Détermination du nom du lexique à partir du nom de fichier (sans extension)
    size_t pos = path.find('.');
    if (pos != string::npos)
        the_name = path.substr(0, pos);
    else
        the_name = DEFAULT_NAME;

    this->nom = the_name;

    // Lecture du contenu du fichier
    (void)readFileIntoString(path, content);

    // Nettoyage du texte
    remove_punctuation(content);
    to_lower(content);

    // Copie du contenu pour traitement
    char* buffer = new char[content.size() + 1];
    strcpy(buffer, content.c_str());

    // Extraction des mots à l’aide de strtok()
    pch = strtok(buffer, delimeters);

    while (pch != NULL)
    {
        if (!this->mots.count(pch))
            this->mots.insert(pair<string, int>(pch, 1));
        else
            this->mots[pch]++;

        pch = strtok(NULL, delimeters);
    }

    delete[] buffer;
}

/**
 * @brief Affiche le contenu complet du lexique (mot et occurrences).
 */
void Lexique::print()
{
    cout << "Lexique from " << this->nom << ":" << endl;
    cout << "Word" << " " << "Occurences" << endl;

    for (map<string, int>::iterator itmap = this->mots.begin();
         itmap != this->mots.end();
         ++itmap)
    {
        cout << itmap->first << " " << itmap->second << endl;
    }
}

/**
 * @brief Retourne le nom du lexique.
 */
string Lexique::get_nom() const
{
    return this->nom;
}

/**
 * @brief Retourne la map des mots du lexique.
 */
const map<string, int>& Lexique::get_mots() const {
    return mots;
}

/**
 * @brief Sauvegarde le contenu du lexique dans un fichier texte.
 * 
 * @return true si la sauvegarde a réussi, false sinon.
 */
bool Lexique::save()
{
    string nomFichier = this->nom + "output_file.txt";
    ofstream output_file(nomFichier);

    if (!output_file)
    {
        cerr << "Erreur d'ouverture du fichier !" << endl;
        return false;
    }

    // Écriture de tous les mots et leurs occurrences dans le fichier
    for (map<string, int>::iterator itmap = this->mots.begin();
         itmap != this->mots.end();
         ++itmap)
    {
        output_file << itmap->first << " " << itmap->second << endl;
    }

    output_file.close();
    cout << "Contenu sauvegardé dans " << nomFichier << endl;
    return true;
}

/**
 * @brief Vérifie la présence d’un mot et retourne son nombre d’occurrences.
 * 
 * @param word mot à rechercher.
 * @return int nombre d’occurrences, 0 si absent.
 */
int Lexique::check_word_presence(string word)
{
    if (this->mots.count(word))
        return this->mots[word];
    else
        return 0;
}

/**
 * @brief Supprime un mot du lexique.
 * 
 * @param word mot à supprimer.
 */
void Lexique::delete_word(string word)
{
    this->mots.erase(word);
}

/**
 * @brief Affiche le nombre de mots différents dans le lexique (sans les occurrences).
 */
void Lexique::print_number_of_words()
{
    int nb=0;
    for (map<string, int>::iterator itmap = this->mots.begin();
         itmap != this->mots.end();
         ++itmap)
    {
        nb++;
    }
    cout << "Il y a dans ce lexique "<<nb<<" mots différents." << endl;
}

/**
 * @brief Surcharge de l’opérateur << pour afficher un lexique complet.
 * 
 * @param os flux de sortie (ex: cout)
 * @param lex lexique à afficher
 * @return ostream& flux modifié (pour chaînage)
 */
ostream& operator<<(ostream& os, const Lexique& lex)
{
    os << "Lexique: " << lex.get_nom() << "\n";
    os << "Mots présents :\n";

    for (map<string, int>::const_iterator it = lex.get_mots().begin();
         it != lex.get_mots().end();
         ++it)
    {
        os << " - " << it->first << " : " << it->second << "\n";
    }

    return os;
}

/**
 * @brief Surcharge de l’opérateur +=
 * Fusionne un autre lexique avec celui-ci : additionne les occurrences.
 * 
 * @param other autre lexique à ajouter.
 */
void Lexique::operator+=(const Lexique& other)
{
    for (map<string, int>::const_iterator it = other.get_mots().begin();
         it != other.get_mots().end();
         ++it)
    {
        this->mots[it->first] += it->second;
    }
}

/**
 * @brief Surcharge de l’opérateur -=
 * Soustrait les occurrences d’un autre lexique. 
 * Si le compteur devient nul ou négatif, le mot est supprimé.
 * 
 * @param other autre lexique à soustraire.
 */
void Lexique::operator-=(const Lexique& other)
{
    for (map<string, int>::const_iterator it = other.get_mots().begin();
         it != other.get_mots().end();
         ++it)
    {
        this->mots[it->first] -= it->second;

        if (this->mots[it->first] <= 0)
            this->mots.erase(it->first);
    }
}
