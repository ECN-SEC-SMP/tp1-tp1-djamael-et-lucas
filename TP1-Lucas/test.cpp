/* fichier de test pour la classe Lexique et Lexique_her */

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include "lexique.h"
#include "lexique_her.h"
#include "test.h"

using namespace std;

//test de la méthode : sauvegarder le contenu du lexique ainsi produit dans un fichier de sortie
void test_partie1_methode1() {
    Lexique lexique;

    lexique.SetNom("MonLexique_partie1");
    cout << "Lexique : <" << lexique.GetNom() << "> a bien ete cree." << endl;

    //Sauvegarder le lexique d'entrée dans le dossier tp1-Lexique-output
    lexique.sauvegarderLexique("LexiqueDeLucas.txt");
    cout << "Le lexique a ete sauvegarde dans le fichier tp1-Lexique-output/Lexique-Lucas-output.txt" << endl;
}

//test de la méthode : tester la présence d'un mot dans le lexique et retourner son nombre d'occurrences
void test_partie1_methode2() {
    Lexique lexique;
    lexique.SetNom("MonLexique_partie2");
    cout << "Lexique : <" << lexique.GetNom() << "> a bien ete cree." << endl;

    string mot;
    cout << "Entrez un mot a tester dans le lexique : ";
    cin >> mot;
    int occurrences = lexique.testerMot(mot);
    if (occurrences > 0) {
        cout << "Le mot <" << mot << "> est present dans le lexique avec " << occurrences << " occurrences." << endl;
    } else {
        cout << "Le mot <" << mot << "> n'est pas present dans le lexique." << endl;
    }
}

//test de la méthode : supprimer un mot du lexique
void test_partie1_methode3() {
    Lexique lexique;
    lexique.SetNom("MonLexique_partie3");
    cout << "Lexique : <" << lexique.GetNom() << "> a bien ete cree." << endl;

    string mot;
    cout << "Entrez un mot a supprimer du lexique : ";
    cin >> mot;
    lexique.supprimerMot(mot);
    //Vérifier que le mot a bien été supprimé
    int occurrences = lexique.testerMot(mot);
    if (occurrences == 0) {
        cout << "Verification : Le mot <" << mot << "> a bien ete supprime du lexique." << endl;
    } else {
        cout << "Verification : Le mot <" << mot << "> est toujours present dans le lexique avec " << occurrences << " occurrences." << endl;
    }
}

//test de la méthode : afficher le nombre de mots différents dans le lexique
void test_partie1_methode4() {
    Lexique lexique;
    lexique.SetNom("MonLexique_partie4");
    cout << "Lexique : <" << lexique.GetNom() << "> a bien ete cree." << endl;

    int nombreMots = lexique.nombreMotsDifferents();
    cout << "Le lexique contient " << nombreMots << " mots differents." << endl;
}

//test de la méthode : Construire le lexique avec lignes
void test_partie2() {
    Lexique_her lexiqueHer;
    lexiqueHer.SetNom("MonLexique_herite");
    cout << "Lexique herite : <" << lexiqueHer.GetNom() << "> a bien ete cree." << endl;
    lexiqueHer.ConstruireLexiqueAvecLignes("LexiqueDeLucas.txt");
    //Tester la présence d'un mot dans le lexique hérité et afficher les lignes où il apparaît
    string motATesterHer;
    cout << "Entrez un mot a tester dans le lexique herite : ";
    cin >> motATesterHer;
    vector<int> lignes = lexiqueHer.getLignesPourMot(motATesterHer);
    //Afficher le résultat
    if (!lignes.empty()) {
        cout << "Le mot <" << motATesterHer << "> est present dans le lexique herite aux lignes : ";
        for (int ligne : lignes) {
            cout << ligne << " ";
        }
        cout << endl;
    } else {
        cout << "Le mot <" << motATesterHer << "> n'est pas present dans le lexique herite." << endl;
    }
}