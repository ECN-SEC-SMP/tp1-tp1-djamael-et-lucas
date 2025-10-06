/*
 * LUCAS OROS 
 * TP1 - SEC - 06/10/2025
 * CPP - TP1
*/

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include "lexique.h"

using namespace std;


int main()
{
    //Créer une instance de la classe Lexique
    Lexique lexique;
    lexique.SetNom("MonLexique_1");
    //afficher le nom du lexique
    cout << "Lexique : <" << lexique.GetNom() << "> a bien ete cree." << endl;

    //Sauvegarder le lexique d'entrée dans le dossier tp1-Lexique-output
    lexique.sauvegarderLexique("LexiqueDeLucas.txt");

    //Tester la présence d'un mot dans le lexique et afficher son nombre d'occurrences
    string motATester;
    cout << "Entrez un mot a tester dans le lexique : ";
    cin >> motATester;
    int occurrences = lexique.testerMot(motATester);
    //Afficher le résultat
    if (occurrences > 0) {
        cout << "Le mot <" << motATester << "> est present dans le lexique avec " << occurrences << " occurrences." << endl;
    } else {
        cout << "Le mot <" << motATester << "> n'est pas présent dans le lexique." << endl;
    }

    //Supprimer un mot du lexique
    string motASupprimer;
    cout << "Entrez un mot a supprimer du lexique : ";
    cin >> motASupprimer;
    lexique.supprimerMot(motASupprimer);
    //Vérifier que le mot a bien été supprimé
    occurrences = lexique.testerMot(motASupprimer);
    if (occurrences == 0) {
        cout << "Verification : Le mot <" << motASupprimer << "> a bien ete supprime du lexique." << endl;
    } else {
        cout << "Verification : Le mot <" << motASupprimer << "> est toujours present dans le lexique avec " << occurrences << " occurrences." << endl;
    }

    //Afficher le nombre de mots différents dans le lexique
    int nombreMots = lexique.nombreMotsDifferents();
    cout << "Le lexique contient " << nombreMots << " mots differents." << endl;

    return 0;
}

