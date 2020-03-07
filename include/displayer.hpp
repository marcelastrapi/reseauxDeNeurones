#pragma once

#include <iostream>

// Pour présenter les choses
using std::cerr;
using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::to_string;

namespace displayer {
    const string GRAS="\x1B[1m";
    const string SOUL="\x1B[4m";

    const string NOIR="\x1B[30m";
    const string ROUGE="\x1B[31m";
    const string VERT="\x1B[32m";
    const string JAUNE="\x1B[33m";
    const string BLEU="\x1B[34m";
    const string VIOLET="\x1B[35m";
    const string BLEUClaire="\x1B[36m";
    const string BLANC="\x1B[37m";

    const string NOIRbg="\x1B[40m";
    const string ROUGEbg="\x1B[41m";
    const string VERTbg="\x1B[42m";
    const string JAUNEbg="\x1B[43m";
    const string BLEUbg="\x1B[44m";
    const string VIOLETbg="\x1B[45m";
    const string BLEUClairebg="\x1B[46m";
    const string BLANCbg="\x1B[47m";

    const string FIN="\x1B[0m";

    const string PROGR_NAME = "Zone d'apprentissage";

    inline void h1(string titre);

    inline void h2(string titre);

    void aide();

    void note(const string& text);

    void log(const string& text);

    template <class T>
        void show(const string& nomVal, T val) 
        {
            cerr << "\t" << GRAS << nomVal << " => " << GRAS << ROUGE << "|" << FIN << to_string(val) << GRAS << ROUGE << "|" << FIN << endl;
        }

    inline void error(const string& text);

    string ask(const string& text);

}
