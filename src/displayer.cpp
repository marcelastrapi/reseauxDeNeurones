#include <displayer.hpp>


inline void displayer::h1(string titre) {
        for (char& c : titre ) c = static_cast<char>(std::toupper(c));
        cout << "\n" << JAUNEbg  << "\n\t\t\t" << NOIR << SOUL << titre << FIN <<  "\n" << endl ;
    }

inline void displayer::h2(string titre) {
    cout << "\n\t\t" << BLEUbg  << "\t" << NOIR << titre << FIN << BLEUbg << "\t" << FIN << endl;
}

void displayer::aide()
{
    h1("Aide pour " + PROGR_NAME);
    cout << "\tRegarde les petits poissons apprendre à nager\n" << endl;

    /* h2("En argument du programme"); */
    /* cout << "\t" << GRAS << "-w " << SOUL << "int" << FIN << "\tLargeur en pixel " << JAUNE << "default:" << GRAS << "Fullscreen" << FIN << endl; */
    /* cout << "\t" << GRAS << "-h " << SOUL << "int" << FIN << "\tHauteur en pixel" << endl; */
    /* cout << "\t" << GRAS << "-n " << SOUL << "int" << FIN << "\tNombre de cell par ligne" << endl; */
    /* cout << "\t" << GRAS << "-t " << SOUL << "int" << FIN << "\tTemps entre chaque step (en ms)" << JAUNE << " [60]" << FIN << endl; */

    /* // Terminal */
    /* cout << endl; */
    /* cout << "\t" << GRAS << "--term " << "\tMode " << VERTbg << NOIR << "TERMINAL" << FIN << endl; */
    /* cout << "\t   " << GRAS << "-a " << SOUL << "char" << FIN << "\tchar for" << GRAS << " a" << FIN << "live cell\n"; */ 
    /* cout << "\t   " << GRAS << "-d " << SOUL << "char" << FIN << "\tchar for" << GRAS << " d" << FIN << "ead  cell\n"; */
    /* cout << endl; */

    /* cout << "\t" << GRAS << "--help" << FIN << "\taffiche cette aide\n\n"; */

    /* h2("Dans la fenêtre"); */
    /* cout << GRAS << "\tr" << FIN << "\tReboot le tableau de cells\n"; */
    /* cout << GRAS << "\tc" << FIN << "\tClear le tableau de cells\n"; */
    /* cout << GRAS << "\tspace" << FIN << "\tToggle pause/play\n"; */
    /* cout << GRAS << "\tk" << FIN << "\tChange la couleur des cells\n"; */
    /* cout << GRAS << "\tb" << FIN << "\tChange la couleur du background\n"; */
    /* cout << GRAS << "\ttab" << FIN << "\tChange la forme des cells (cercle, rectangle)\n"; */
    /* cout << GRAS << "\tt" << "\tMode t" << FIN << "empo des étapes\n"; */
    /* cout << GRAS << "\tn" << "\tMode n" << FIN << "ombeDeCellParLigne\n"; */
    /* cout << GRAS << "\tv" << "\tMode r" << FIN << "everse\n"; */
    /* cout << GRAS << "\t+" << FIN << "\tAugmente selon le mode" << JAUNE << " (ou molette de souris)" << FIN << endl; */
    /* cout << GRAS << "\t-" << FIN << "\tDiminue selon le mode\n"; */

    /* h2("Formes"); */
    /* cout << GRAS << "\tg" << FIN << "\tGlider\n"; */
    /* cout << GRAS << "\tl" << FIN << "\tLigne verticales" << JAUNE << " (modifiable)" << FIN << endl; */
    /* cout << GRAS << "\th" << FIN << "\tLigne horizontales" << JAUNE << " (modifiable)" << FIN << endl; */
    /* cout << GRAS << "\ts" << FIN << "\tSquare" << JAUNE << " (modifiable)" << FIN << endl; */
    /* cout << GRAS << "\tx" << FIN << "\tCross" << JAUNE << " (modifiable)" << FIN << endl;; */

    /* h2("Basics"); */
    /* cout << GRAS << "\tEscape" << FIN << "\tQuit\n"; */

    /* cout << endl; */
    exit(0);
}

void displayer::note(const string& text) {
    cout << BLEU << text << FIN << endl;
}

void displayer::log(const string& text) {
    cerr << "\t" << GRAS << text << endl << FIN;
}


// template <class T>
// void show(const T multi) {
//   for (const auto& elem : multi )
//     cerr << "\t" << GRAS << elem.first << " => " << GRAS << ROUGE << "|" << FIN << elem.second << GRAS << ROUGE << "|" << FIN << endl;
// }

inline void displayer::error(const string& text) {
    cout << ROUGEbg << NOIR << text << FIN << endl;
}

string displayer::ask(const string& text) {

    cout << VIOLET << text << FIN;
    string rep;
    getline(cin,rep);
    return rep;

}
