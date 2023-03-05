#include <SFML/Graphics.hpp>

#include <algorithm>
#include <cstddef>
#include <rnd.hpp>
#include <displayer.hpp>
using namespace displayer;
#include <coord.hpp>
#include <utils.hpp>

using std::vector;

#include <monde.hpp>
#include <requin.hpp>

//////////////////////////
// Déclaration générale //
//////////////////////////
auto windowStyle = sf::Style::Fullscreen;
auto secondaryWindowStyle = sf::Style::Close;
sf::RenderWindow* myWindow;
/*
   enum Style {
   None = 0,
   Titlebar = 1 << 0,
   Resize = 1 << 1,
   Close = 1 << 2,
   Fullscreen = 1 << 3
   }
   */

enum CellShape { circle = 0, rectangle = 1 };
CellShape cellShape = circle;
unsigned char nbCellShape = 2;
float cellWidthDivBy2;
sf::Vector2f vector2fRectangleSize;

bool play = true;



unsigned int minWinWidth = 4;
unsigned int minWinHeight = 4;
unsigned int windowWidth  = 0; // Default, fullscreen
unsigned int windowHeight = 0;

int tickTime = 41; // 24 image/s = 41.66 ms
short incrTickTime = 2; // en ms
int minTickTime = 1; // en ms

vector<sf::Color> colors;
sf::Color bgColor = sf::Color::Black;

bool iDrawSomething = true;

sf::Text noteText;
sf::Clock clockText;
unsigned int textTime = 3; // en seconde

sf::Text tauxDeCarnageText;
sf::Clock clockTauxDeCarnage;
int tauxDeCarnageTime = 1; // en seconde

sf::Clock clockDuMonde;
int tempsDuMonde = 10; // en millisecond
int incrTempsDuMonde = 1;
int minTempsDuMonde = 0;

Coord posReqInit; // position initial pour le requin
Coord posPoiInit; // position initial pour le poisson

// Je veux des poissons
unsigned int nombreDePoissons = 1000; // multiple de 10 obligatoire
unsigned int nbHiddenLayers = 6;
unsigned int nbNeuroneParHiddenLayers = 20;
unsigned int nbInput = 6;
float poidsMin(-1), poidsMax(1);
nbType valBiais = 1;
Couleur clPoisson = Couleur(0,255,0);
Etre::nbType taillePoisson = 10;

unsigned int pourcentageASelectionner = 10;
/* float fourchetteDeBase = 1 / (float)nombreDePoissons; */
float fourchetteDeBase = 1;

unsigned int nbGeneration = 0;

unsigned int tempsAttenteDuRequin = 200;

Tic selectionTime(40000);

enum Mode
{
    TEMPS_DU_MONDE,
    TEMPS_AFFICHAGE
};
Mode mode = TEMPS_DU_MONDE;

size_t nbRequins(1);
vector<Requin*> requins;
/* Requin* requin2; */
vector<Poisson*> poissons;
unsigned int indexPoisson = 0;

bool modeMouseOn = false;
bool modeGraphique = true;

//////////////////////////////////////////////////////////////////////
// Functions
//////////////////////////////////////////////////////////////////////

bool gereLesArguments( vector<string>& args )
{
    if  ( args.size() > 0 )
    {
        string oldArg;
        for ( string& curArg : args )
        {
            if ( oldArg == "-w" ) {
                displayer::note("windowWidth set manually: " + curArg);
                windowStyle = secondaryWindowStyle;
                windowWidth = static_cast<unsigned int>(std::stoi(curArg));
            }

            if ( oldArg == "-h" ) {
                displayer::note("windowHeight set manually: " + curArg);
                windowStyle = secondaryWindowStyle;
                windowHeight = static_cast<unsigned int>(std::stoi(curArg));
            }

            if ( curArg == "--help" || ( curArg == "-h" && args.size() == 1) ) displayer::aide();
            oldArg = curArg;

        }

    }
    return true;
}

void notify(const string &text)
{
    displayer::note(text);
    noteText.setString(text);
    iDrawSomething = true;
    clockText.restart();
}

// Functions
void creerToutLesEtres(Monde& monde)
{
    note("Création de tout les êtres dans le monde");
    // C'est ici que je décide ce qui constitue ce monde.

    // Il va y avoir pleins de poissons qui pourront se déplacer à la surface du
    // monde

    // et un requin qui va passer son temps à les manger.

    // Le but est d'essayer de voir comment les poissons générations
    // après générations d'auto-clonages pourront apprendre à esquiver le
    // requin.

    // Je veux n requin.s
    Requin* requin;
    for (size_t i=0; i < nbRequins; i++)
    {
        requin = new Requin();
        requin->dimensionDuMonde(monde.largeur(), monde.hauteur());
        requin->dimension(30, 30.f);
        requin->couleur(Couleur(255,0,0));
        requin->maxDistanceDeDéplacement(3);
        /* requin->maxAngleDeDirection(3.14f/4.f); */
        requin->posAléa();
        /* requin->mouvant(false); */
        requins.push_back(requin);
    }


    // Je veux des poissons
    for (unsigned int i = 0; i < nombreDePoissons; i++)
    {
        Poisson* p = new Poisson();
        p->i = i;
        p->dimensionDuMonde(monde.largeur(),monde.hauteur());
        p->dimension(taillePoisson,taillePoisson);
        /* p->posAléa(); */
        p->pos(monde.largeur()*0.5f, monde.hauteur()*0.5f);
        p->couleur(clPoisson);
        p->maxDistanceDeDéplacement(requin->maxDistanceDeDéplacement());
        /* p->maxDistanceDeDéplacement(1); */
        // nbRequins + 2 pour la pos du poisson
        p->réseauDeNeurones().nbNeuronesInput(nbInput);
        p->réseauDeNeurones().nbHiddenLayers(nbHiddenLayers, nbNeuroneParHiddenLayers);
        for (auto& hiddenLayer: p->réseauDeNeurones().hiddenLayers()){
            hiddenLayer.emplace_back(Neurone(valBiais,true));
        };
        p->réseauDeNeurones().nbNeuronesOutput(1);
        p->réseauDeNeurones().connecteLesLignesEntreElles();
        p->réseauDeNeurones().poidsAléa(poidsMin,poidsMax);
        /* p->réseauDeNeurones().print(); */

        poissons.push_back(p);
        /* monde.ajouteEtre(p); */
        /* requins.at(i)->ajouteCible(p); */
        /* for (Requin* requin: requins) */
        /*     requin->ajouteCible(p); // héhéhéé */
    }

    indexPoisson = 0;
    poissons.at(0)->pos(monde.largeur()*0.5f, monde.hauteur()*0.5f);
    monde.ajouteEtre(poissons.at(0));

    for (Requin* requin: requins)
    {
        requin->ajouteCible(poissons.at(0)); // héhéhéé
    }
    /* monde.print(); */

    // j'ajoute le requin dans le monde
    // (en dernier pour qu'il soit dessiner sur les poissons
    for (Requin* requin: requins)
        monde.ajouteEtre(requin);

    note("Création du monde avec leurs habitants TERMINÉ");
}

Requin* meilleursRequin()
{
    Requin* meilleursRequin = requins.at(0);
    auto topNbCiblesMangées = meilleursRequin->nbCiblesMangées();
    for (Requin* r: requins)
    {
        if (r->nbCiblesMangées() > topNbCiblesMangées)
        {
            topNbCiblesMangées = r->nbCiblesMangées();
            meilleursRequin = r;
        }
    }
    return meilleursRequin;
}

Poisson* meilleursPoisson()
{
    Poisson* meilleursPoisson = poissons.at(0);
    auto topPlusGrandTempsDeVie = meilleursPoisson->plusGrandTempsDeVie();
    for (Poisson* p: poissons)
    {
        if (p->plusGrandTempsDeVie() > topPlusGrandTempsDeVie)
        {
            topPlusGrandTempsDeVie = p->plusGrandTempsDeVie();
            meilleursPoisson = p;
        }
    }
    return meilleursPoisson;
}

void selectionneEtRepliqueMeilleursPoisson(const Monde& monde)
{
    Requin* killerShark = meilleursRequin();
    Poisson* survivorFish = meilleursPoisson();

    survivorFish->print();

    /* for (Requin* r: requins) r->posAléa(); */

    notify(
            "Meilleurs score pour un requin: "          +
            to_string(killerShark->nbCiblesMangées())   +
            "\n"                                        +
            "Plus long temps de vie pour un poisson: "  +
            to_string(survivorFish->plusGrandTempsDeVie())
          );

    // Je réinit à 0 les nbCiblesMangées
    for (Requin* r: requins) r->nbCiblesMangées(0);

    /* nbType fourchetteAutourDuPoids(1/((float)monde.ticDepuisCréation()/(float)selectionTime)); */
    /* int nbGeneration = monde.ticDepuisCréation() / selectionTime; */

    nbType fourchetteAutourDuPoids(0.1/nbGeneration);
    /* show("nbGeneration",nbGeneration); */
    /* show("fourchetteAutourDuPoids",fourchetteAutourDuPoids); */
    /* show("fourchetteAutourDuPoids",fourchetteAutourDuPoids); */
    /* if (fourchetteAutourDuPoids > 1) fourchetteAutourDuPoids = 1; */
    if (fourchetteAutourDuPoids < 0.005) fourchetteAutourDuPoids = 0.005;
    show("fourchetteAutourDuPoids",fourchetteAutourDuPoids);
    for (Poisson* p: poissons)
    {
        p->plusGrandTempsDeVie(0);
        p->réseauDeNeurones(survivorFish->réseauDeNeurones());
        p->réseauDeNeurones().poidsAléa(fourchetteAutourDuPoids);
    }
}

// Sub
bool comparePtrToNode(Poisson* a, Poisson* b) { return (a->plusGrandTempsDeVie() > b->plusGrandTempsDeVie()); }

////////////////////////////////////////////////////
//                    MAIN                        //
////////////////////////////////////////////////////
int main (int argc, char* argv[] )
{
    // Convertion le tableau d'argument en vector (plus pratique)
    vector<string> args;
    for ( int i(1) ; i < argc ; i++ )
    {
        args.push_back(argv[i]);
    }

    gereLesArguments(args);

    Rnd::randomize();

    ////////////////////////////////////////
    // TEST
    ////////////////////////////////////////

    /* Poisson* e1 = new Poisson(); */
    /* e1->réseauDeNeurones().nbHiddenLayers(2,2); */
    /* e1->réseauDeNeurones().connecteLesLignesEntreElles(); */
    /* e1->réseauDeNeurones().poidsAléa(0,10); */
    /* e1->réseauDeNeurones().hiddenLayers().at(0).at(0).print(); */
    /* Poisson* e2 = new Poisson(); */
    /* e2->réseauDeNeurones().nbHiddenLayers(2,2); */
    /* e2->réseauDeNeurones().connecteLesLignesEntreElles(); */
    /* e2->réseauDeNeurones().poidsAléa(10,20); */
    /* e2->réseauDeNeurones().hiddenLayers().at(0).at(0).print(); */
    /* show("e1==e2", e1->réseauDeNeurones() == e2->réseauDeNeurones()); */
    /* e2->réseauDeNeurones(e1->réseauDeNeurones()); */
    /* show("e1==e2", e1->réseauDeNeurones() == e2->réseauDeNeurones()); */
    /* e2->réseauDeNeurones().poidsAléa(-1,0); */
    /* show("e1==e2", e1->réseauDeNeurones() == e2->réseauDeNeurones()); */
    /* /1* e2->print(); *1/ */

    /* réseauDeNeurones.output().poidsAléa(0,1); */

    /* RéseauDeNeurones::TblValeurs tblValeursEnEntrée = { 2 }; */
    /* réseauDeNeurones.tableauxDesValeursEnEntrée(tblValeursEnEntrée); */

    /* réseauDeNeurones.calculeLesValeursDeToutMesNeurones(); */

    /* for (auto val: réseauDeNeurones.tableauxDesRésultats()) */
    /*     show("val",val); */

    /* réseauDeNeurones.print(true); */

    /* return 0; */

    ////////////////////////////////////////


    // Initialize colors tbl
    colors.push_back(sf::Color::Red);
    colors.push_back(sf::Color::Green);
    colors.push_back(sf::Color::Yellow);
    colors.push_back(sf::Color::White);
    colors.push_back(sf::Color::Black);
    colors.push_back(sf::Color::Magenta);
    colors.push_back(sf::Color::Cyan);

    /*     sf::ContextSettings settings; */
    /*     settings.antialiasingLevel = 8; */

    auto screenSize = sf::VideoMode::getDesktopMode();

    if (!windowWidth) windowWidth = screenSize.width;
    if (!windowHeight) windowHeight = screenSize.height;

    if (windowWidth > screenSize.width) windowWidth = screenSize.width;
    if (windowHeight > screenSize.height) windowHeight = screenSize.height;

    show("windowWidth",windowWidth);
    show("windowHeight",windowHeight);
    show("tickTime",tickTime);

    // Création de la fenêtre
    sf::RenderWindow window(
            sf::VideoMode(windowWidth,windowHeight),
            "Apprentissage",
            windowStyle);//,
    /* settings); */

    myWindow = &window;

    // Text infos // TODO mettre le nom en relatif
    sf::Font font;
    font.loadFromFile("/home/pi/.scripts/termine/c++/apprentissage/rsc/NotoMono-Regular.ttf");
    noteText.setFont(font);
    noteText.setCharacterSize(17);
    noteText.setFillColor(sf::Color::Yellow);
    noteText.setPosition(10,10);
    noteText.setStyle( sf::Text::Bold );

    tauxDeCarnageText.setFont(font);
    tauxDeCarnageText.setCharacterSize(17);
    tauxDeCarnageText.setFillColor(sf::Color::Yellow);
    tauxDeCarnageText.setPosition(windowWidth - 100,30);
    tauxDeCarnageText.setStyle( sf::Text::Bold );

    ////////////////////////////////////////// MONDE
    Monde monde(windowWidth,windowHeight);
    creerToutLesEtres(monde);

    auto largeur = monde.largeur();
    auto hauteur = monde.hauteur();
    posReqInit = Coord(0.5f*largeur - 0.1*largeur, 0.5f*hauteur);
    posPoiInit = Coord(0.5f*largeur + 0.1*largeur, 0.5f*hauteur);

    /* monde.print(); */

    sf::Clock clock;
    sf::Clock clockTotalTime;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    displayer::note("Quit");
                    exit(0);
                }

                if (event.key.code == sf::Keyboard::R)
                {
                    for (Requin* requin: requins)
                        requin->renaît();
                    for (Poisson* poisson: poissons)
                        poisson->renaît();
                    notify("Reboot");
                }

                if (event.key.code == sf::Keyboard::Space)
                {
                    play = !play;
                    if (play)
                        notify("PLAY");
                    else
                        notify("PAUSE");
                }

                if (event.key.code == sf::Keyboard::M)
                {
                    if (mode == TEMPS_DU_MONDE) {
                        mode = TEMPS_AFFICHAGE;
                        notify("TEMPS_AFFICHAGE");
                    }else{
                        mode = TEMPS_DU_MONDE;
                        notify("TEMPS_DU_MONDE");
                    }
                }

                if (event.key.code == sf::Keyboard::Left)
                {
                    for (Requin* requin: requins)
                    {
                        requin->angleDeDirection(3.14f);
                        requin->avance();
                    }
                }
                if (event.key.code == sf::Keyboard::Up)
                {
                    for (Requin* requin: requins)
                    {
                        requin->angleDeDirection(3.14f*0.5f);
                        requin->avance();
                    }
                }
                if (event.key.code == sf::Keyboard::Right)
                {
                    for (Requin* requin: requins)
                    {
                        requin->angleDeDirection(0.f);
                        requin->avance();
                    }
                }
                if (event.key.code == sf::Keyboard::Down)
                {
                    for (Requin* requin: requins)
                    {
                        requin->angleDeDirection(-3.14f*0.5f);
                        requin->avance();
                    }
                }

                // Affiche la list des possons avec leurs scores
                if (event.key.code == sf::Keyboard::S)
                {
                    int i = 0;
                    for (Poisson* p: poissons) {
                        show(to_string(i++) + ":", p->nbVictoire());
                    }
                }

                if (event.key.code == sf::Keyboard::O)
                {
                    poissons.at(indexPoisson)->print();
                }

                if (event.key.code == sf::Keyboard::P)
                {
                    meilleursPoisson()->print();
                }

                if (event.key.code == sf::Keyboard::G)
                {
                    if (modeGraphique == true)
                    {
                        modeGraphique = false;
                        notify("mode graphique: false");
                    }else{
                        modeGraphique = true;
                        notify("mode graphique: true");
                    }
                }

                if (event.key.code == sf::Keyboard::D)
                {
                    selectionneEtRepliqueMeilleursPoisson(monde);
                }
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    Requin* requin = requins.at(0);
                    modeMouseOn = true;
                    requin->mouvant(false);
                    requin->pos(event.mouseButton.x,event.mouseButton.y);
                }
            }
            if (event.type == sf::Event::MouseButtonReleased)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    modeMouseOn = false;
                    requins.at(0)->mouvant(true);
                }
            }

            if (event.type == sf::Event::MouseMoved && modeMouseOn)
            {
                requins.at(0)->pos(event.mouseMove.x,event.mouseMove.y);
            }

            if (event.key.code == sf::Keyboard::Add || (event.type == sf::Event::MouseWheelMoved && event.mouseWheel.delta == -1))
            {
                switch (mode)
                {
                    case TEMPS_DU_MONDE:
                        tempsDuMonde -= incrTempsDuMonde;
                        if (tempsDuMonde < minTempsDuMonde) tempsDuMonde = minTempsDuMonde;
                        notify("tempsDuMonde:"+to_string(tempsDuMonde)+"ms");
                        break;

                    case TEMPS_AFFICHAGE:
                        tickTime -= incrTickTime;
                        if (tickTime < minTickTime) tickTime = minTickTime;
                        notify("tickTime:"+to_string(tickTime)+"ms");
                        break;
                }
            }
            if (event.key.code == sf::Keyboard::Subtract || (event.type == sf::Event::MouseWheelMoved && event.mouseWheel.delta == 1))
            {
                switch (mode)
                {
                    case TEMPS_DU_MONDE:
                        tempsDuMonde += incrTempsDuMonde;
                        notify("tempsDuMonde:"+to_string(tempsDuMonde)+"ms");
                        break;

                    case TEMPS_AFFICHAGE:
                        tickTime += incrTickTime;
                        notify("tickTime:"+to_string(tickTime)+"ms");
                        break;
                }
            }
        }

        if (clockText.getElapsedTime().asSeconds() >= textTime) {
            iDrawSomething = true;
            noteText.setString("");
        }

        if (clockTauxDeCarnage.getElapsedTime().asSeconds() >= tauxDeCarnageTime) {
            iDrawSomething = true;
            if (requins.size() > 0)
            {
                /* tauxDeCarnageText.setString( to_string(monde.ticDepuisCréation()/(float)selectionTime )); */
                tauxDeCarnageText.setString( to_string(indexPoisson) + "/" + to_string(nbGeneration) );
                clockTauxDeCarnage.restart();
            }
        }

        if (clockDuMonde.getElapsedTime().asMilliseconds() >= tempsDuMonde)
        {
            clockDuMonde.restart();
            if (play)
            {
                // TODO faire en sorte que ce soit le monde qui avant d'un pas plutot que chaque être ici

                // Je regarde si le requin à besoin d'une nouvelle cible

                for (Requin* requin: requins)
                    requin->prendLaDirectionDeLaCibleLaPlusProche();

                RéseauDeNeurones::TblValeurs tblValsInput;

                Poisson* poissonEnLice = poissons.at(indexPoisson);

                tblValsInput.clear();
                for (Requin* requin: requins)
                {
                    /* tblValsInput.emplace_back(requin->angleDeDirection()/3.14f); */
                    tblValsInput.emplace_back(requin->pos().x);
                    tblValsInput.emplace_back(requin->pos().y);
                }

                tblValsInput.push_back(monde.largeur());
                tblValsInput.push_back(monde.hauteur());
                tblValsInput.push_back(poissonEnLice->pos().x);
                tblValsInput.push_back(poissonEnLice->pos().y);

                poissonEnLice->tableauxDesValeursEnEntrée(tblValsInput);
                poissonEnLice->calculeLesValeursDeToutMesNeurones();
                /* poissonEnLice->angleDeDirection( poissonEnLice->réseauDeNeurones().output().at(0).valeur() ); */
                poissonEnLice->angleDeDirection( poissonEnLice->réseauDeNeurones().output().at(0).valeur()*3.14f );
                /* poissonEnLice->angleDeDirection( poissonEnLice->tableauxDesRésultats().at(0)); */
                /* poissonEnLice->réseauDeNeurones().print(true); */

                monde.tic();

                // si le poisson actuel est mort
                if (poissonEnLice->plusGrandTempsDeVie() > 0) {

                    monde.supprimeEtre(poissonEnLice);
                    for (Requin* requin: requins)
                    {
                        requin->supprimeCible(poissonEnLice);
                        requin->pos(posReqInit);
                    }

                    // on passe au poisson suivant
                    indexPoisson++;
                    /* show("indexPoisson",indexPoisson); */

                    // tout les poissons ont participé au concours
                    if (indexPoisson >= poissons.size()) {
                        indexPoisson = 0;
                        ++nbGeneration;

                        // On va trier par ordre de temps de vie
                        std::sort(poissons.begin(), poissons.end(), comparePtrToNode);

                        /* size_t nbRef = nombreDePoissons / pourcentageASelectionner; */
                        /* size_t nbRef = 1; */

                        // TODO BUG
                        // avec 10 poisson, on observe qu'il y a un problème de programmation...
                        Poisson* poissonDeReference = poissons.at(0);

                        note("************************************************************");
                        note("************************************************************");

                        for (auto p = poissons.rbegin(); p != poissons.rend(); ++p)
                        {
                            note(to_string((*p)->i) + "\t->\t" + to_string((*p)->plusGrandTempsDeVie()));
                            (*p)->plusGrandTempsDeVie(0);
                        }
                        /* for (Poisson* p: poissons) */
                        /* { */
                        /*     /1* p->print(); *1/ */
                        /* } */


                        /* poissonDeReference->print(); */
                        /* note("************************************************************"); */
                        size_t iLayer = 0;
                        size_t iNeurone = 0;
                        for (size_t i = 1; i < nombreDePoissons; i++) {
                            Poisson* poissonAModifier = poissons.at(i);
                            /* Poisson* poissonDeReference = poissons.at(i % nbRef); */
                            /* show("index poisson de ref:\t", i%nbRef); */
                            /* show("id poisson ref:\t", poissonDeReference->i); */
                            /* show("index poisson à modifier:\t", i); */
                            /* size_t numGeneration = i/nbRef; */
                            /* size_t numGeneration = 1; */
                            /* show("numGeneration",numGeneration); */
                            /* show("fourchetteDeBase * numGeneration",fourchetteDeBase * numGeneration); */

                            poissonAModifier->réseauDeNeurones(poissonDeReference->réseauDeNeurones());
                            /* poissonAModifier->réseauDeNeurones().poidsAléa( fourchetteDeBase ); */
                            poissonAModifier->réseauDeNeurones().hiddenLayers().at(iLayer).at(iNeurone).poidsAléa(poidsMin, poidsMax);
                            /* show("iLayer",iLayer); */
                            /* show("iNeurone",iNeurone); */
                            iNeurone = (++iNeurone)%nbNeuroneParHiddenLayers;
                            if ( iNeurone == 0 ){
                                iLayer = (++iLayer)%nbHiddenLayers;
                            }
                            /* poissonAModifier->print(); */
                        }

                    }

                    // C'est au tour d'un nouveau poisson
                    Poisson* nouveauPoisson = poissons.at(indexPoisson);
                    /* nouveauPoisson->pos(posPoiInit); */
                    nouveauPoisson->pos(monde.largeur()*0.5f,monde.hauteur()*0.5f);
                    monde.ajouteEtre(nouveauPoisson);
                    /* nouveauPoisson->print(); */

                    for (Requin* requin: requins)
                        requin->ajouteCible(nouveauPoisson);

                    /* show("nbCible req 0", requins.at(0)->nbCibles()); */

                }


                /* if (monde.ticDepuisCréation() % selectionTime == selectionTime-1) */
                /*     selectionneEtRepliqueMeilleursPoisson(monde); */

                /* requin2->avance(); */
            }
        }

        /* Ici on dessine le monde */
        if (clock.getElapsedTime().asMilliseconds() >= tickTime )
        {
            clock.restart();

            // Comme ca je ne redessine pas 2 fois de suite la même image
            if (!iDrawSomething) iDrawSomething = false;

            window.clear(bgColor);


            // Je dessine tout le monde
            if (modeGraphique) {
                Etre* etre;
                sf::Color cl;
                Couleur* mcl;
                Etre::nbType posx,posy;
                for (unsigned int i = 0; i < monde.getNbEtres(); i++)
                {
                    etre = monde.at(i);
                    mcl = &etre->couleur();
                    cl = sf::Color(mcl->r,mcl->g,mcl->b,mcl->a);
                    posx = etre->left();
                    posy = etre->top();

                    /* etre->print(); */
                    switch (etre->forme())
                    {
                        case Cercle:
                            {
                                sf::CircleShape circle(etre->largeur()*0.5f);
                                circle.setFillColor(cl);
                                circle.setPosition(posx , posy);
                                /* circle.setRotation(radToDeg(etre->angleDeDirection())); */

                                /* note("pos:"+to_string(pos->x)+","+to_string(pos->y)); */
                                window.draw(circle);
                                iDrawSomething = true;

                                break;
                            }

                        case Rectangle:
                            {
                                sf::RectangleShape rect(sf::Vector2f(etre->largeur(),etre->hauteur()));
                                rect.setFillColor(cl);
                                rect.setPosition(posx , posy);
                                /* rect.setRotation(-radToDeg(etre->angleDeDirection())); */
                                window.draw(rect);
                                iDrawSomething = true;

                                break;
                            }

                    }
                }
            }

            window.draw(noteText);
            window.draw(tauxDeCarnageText);

            if (iDrawSomething) window.display();
            /* play = false; */
        }
    }

    for (Requin* r: requins)
        delete r;
}
