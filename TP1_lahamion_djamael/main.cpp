#include "Lexique.h"
#include "LexiqueAvecLignes.h"

// Fonction utilitaire pour afficher si un mot est présent dans un lexique et combien de fois
void afficher_presence_lexique(Lexique* Lexique, string& word);

int main()
{
    // Création de deux lexiques à partir de fichiers texte
    // Lexique* Lexique1 = new Lexique("tp1-Lexique-fichiers/lesMiserables_A.txt");
    // Lexique* Lexique2 = new Lexique("tp1-Lexique-fichiers/notreDameDeParis_A.txt");

    // Utilisation de fichiers tests plus courts
    Lexique* Lexique1 = new Lexique("tp1-Lexique-fichiers/Lexique1.txt");
    Lexique* Lexique2 = new Lexique("tp1-Lexique-fichiers/Lexique2.txt");

    // Création d'un lexique avec suivi des lignes
    LexiqueAvecLignes lex("tp1-Lexique-fichiers/Lexique1.txt");

    // Sauvegarde du lexique1 dans un fichier de sortie
    Lexique1->save();

    // Affichage des deux lexiques dans la console
    cout << *Lexique1 << endl;
    cout << *Lexique2 << endl;

    // Définition du mot à rechercher et tester
    string word = "these";
    
    // Vérification de la présence du mot dans le lexique1
    afficher_presence_lexique(Lexique1, word);

    // Suppression du mot du lexique1
    cout << "Suppression du mot " << word << endl;
    Lexique1->delete_word(word);

    // Vérification de la présence après suppression
    afficher_presence_lexique(Lexique1, word);

    // Réaffichage du lexique1 pour confirmer la suppression
    cout << *Lexique1 << endl;

    // Réaffichage du lexique2
    cout << *Lexique2 << endl;

    // Affichage du nombre total de mots différents dans le lexique2
    Lexique2->print_number_of_words();
    
    // Exemple de fusion et différence des lexiques
    cout << "Fusion des lexiques" << endl;
    *Lexique2 += *Lexique1;  // Ajout des mots de lexique1 dans lexique2
    cout << *Lexique2 << endl;

    cout << "Difference des lexiques" << endl;
    *Lexique2 -= *Lexique1;  // Retrait des mots de lexique1 de lexique2
    cout << *Lexique2 << endl;

    // Travail avec le lexique qui contient les lignes
    cout << "Lexique Avec lignes" << endl;
    cout << lex << endl;  // Affichage du lexique avec lignes
    lex.print();          // Affichage détaillé avec les numéros de lignes

    return 0;
}

// Fonction pour tester la présence d'un mot dans un lexique et afficher le résultat
void afficher_presence_lexique(Lexique* Lexique, string& word)
{
    cout << "Test de la présence du mot '" << word 
         << "' dans le Lexique " << Lexique->get_nom() << endl;

    int occurenceThese = Lexique->check_word_presence(word);

    if (occurenceThese == 0)
    {
        cout << "Le mot n'est pas présent" << endl;
    }
    else
    {
        cout << "Le mot est présent " << occurenceThese << " fois" << endl;
    }
}
