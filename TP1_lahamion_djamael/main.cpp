#include "Lexique.h"
#include "LexiqueAvecLignes.h"

int main()
{
    // Lexique* Lexique1 = new Lexique("tp1-Lexique-fichiers/lesMiserables_A.txt");
    // Lexique* Lexique2 = new Lexique("tp1-Lexique-fichiers/notreDameDeParis_A.txt");

    Lexique* Lexique1 = new Lexique("tp1-Lexique-fichiers/Lexique1.txt");
    Lexique* Lexique2 = new Lexique("tp1-Lexique-fichiers/Lexique2.txt");
    LexiqueAvecLignes lex("tp1-Lexique-fichiers/Lexique1.txt");



    // Lexique1->print();
    // Lexique2->print();

    Lexique1->save();
    cout << *Lexique1 << endl;
    cout << *Lexique2 << endl;

    cout<<"Test de la présence du mot these dans le premier Lexique"<<endl;
    int occurenceThese=Lexique1->check_word_presence("these");
    if(occurenceThese == 0)
    {
        cout<<"Le mot n'est pas présent"<<endl;
    }else
    {
        cout<<"Le mot est present "<<occurenceThese<<" fois"<<endl;
    }

    Lexique1->delete_word("these");
    cout<<"Test de la présence du mot these dans le premier Lexique après suppression"<<endl;
    occurenceThese=Lexique1->check_word_presence("these");
    if(occurenceThese == 0)
    {
        cout<<"Le mot n'est pas présent"<<endl;
    }else
    {
        cout<<"Le mot est present "<<occurenceThese<<" fois"<<endl;
    }
    cout << *Lexique1 << endl;

    cout << *Lexique2 << endl;
    Lexique2->print_number_of_words();
    
    // *Lexique1+=*Lexique2;
    // *Lexique1-=*Lexique2;

    cout<< "Fusion des lexiques"<<endl;
    *Lexique2+=*Lexique1;
    cout << *Lexique2 << endl;

    cout<< "Difference des lexiques"<<endl;
    *Lexique2-=*Lexique1;
    cout << *Lexique2 << endl;

    cout<< "Lexique Avec lignes"<<endl;
    cout<<lex<<endl;
    lex.print();

}