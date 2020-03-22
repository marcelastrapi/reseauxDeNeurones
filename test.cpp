#include <reseauDeNeurones.cpp>

#include <displayer.cpp>

int main()
{

    string rep;

    note("\n============================================================");
    note("\t\t\tTEST EN COURS");
    note("============================================================\n");

    RéseauDeNeurones r(2,3,4,1);

    r.poidsAléa(3);

    RéseauDeNeurones c(r);

    r.print(true);
    cin >> rep;
    c.print(true);

    return 0;
}
