#include <SFML/Graphics.hpp>

#include <rnd.hpp>
#include <displayer.hpp>
using namespace displayer;

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
int tempsDuMonde = 0; // en millisecond
int incrTempsDuMonde = 1;
int minTempsDuMonde = 0;

Tic selectionTime(40000);

enum Mode
{
    TEMPS_DU_MONDE,
    TEMPS_AFFICHAGE
};
Mode mode = TEMPS_DU_MONDE;

vector<Requin*> requins;
/* Requin* requin2; */
vector<Poisson*> poissons;

bool modeMouseOn = false;

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
    size_t nbRequins(3);
    Requin* requin;
    for (size_t i=0; i < nbRequins; i++)
    {

        requin = new Requin();
        requin->dimensionDuMonde(monde.largeur(), monde.hauteur());
        requin->dimension(30, 30.f);
        requin->couleur(Couleur(255,0,0));
        requin->maxDistanceDeDéplacement(1);
        requin->maxAngleDeDirection(3.14f/4.f);
        requin->posAléa();
        /* requin->mouvant(false); */
        requins.push_back(requin);
    }

    /* requin2 = new Requin(); */
    /* requin2->dimensionDuMonde(monde.largeur(), monde.hauteur()); */
    /* requin2->dimension(30, 30.f); */
    /* requin2->couleur(Couleur(0,0,255)); */
    /* requin2->posAléa(); */
    /* requin2->maxDistanceDeDéplacement(10); */
    /* requin2->maxAngleDeDirection(0.3f); */
    /* requin2->print(); */

    // Je veux des poissons
    unsigned int nombreDePoissons = 200;
    Couleur clPoisson = Couleur(0,255,0);
    Etre::nbType taillePoisson = 10;

    for (unsigned int i = 0; i < nombreDePoissons; i++)
    {
        Poisson* p = new Poisson();
        p->dimensionDuMonde(monde.largeur(),monde.hauteur());
        p->dimension(taillePoisson,taillePoisson);
        p->posAléa();
        p->couleur(clPoisson);
        p->maxDistanceDeDéplacement(requin->maxDistanceDeDéplacement() +2 );
        p->réseauDeNeurones().nbNeuronesInput(nbRequins + 2);
        p->réseauDeNeurones().nbHiddenLayers(2,9);
        p->réseauDeNeurones().nbNeuronesOutput(1);
        p->réseauDeNeurones().connecteLesLignesEntreElles();
        p->réseauDeNeurones().poidsAléa(-1,1);
        p->réseauDeNeurones().seuil(-4);
        p->réseauDeNeurones().output().at(0).seuil(-10000000);
        p->réseauDeNeurones().print();

        poissons.push_back(p);
        monde.ajouteEtre(p);
        /* requins.at(i)->ajouteCible(p); */
        for (Requin* requin: requins)
            requin->ajouteCible(p); // héhéhéé
    }

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

    for (Requin* r: requins) r->posAléa();

    notify( "Meilleurs score pour un requin: "          +
            to_string(killerShark->nbCiblesMangées())   +
            "\n"                                        +
            "Plus long temps de vie pour un poisson: "  +
            to_string(survivorFish->plusGrandTempsDeVie()));

    // Je réinit à 0 les nbCiblesMangées
    for (Requin* r: requins) r->nbCiblesMangées(0);

    /* nbType fourchetteAutourDuPoids(1/((float)monde.ticDepuisCréation()/(float)selectionTime)); */
    nbType fourchetteAutourDuPoids(0.1);
    /* show("fourchetteAutourDuPoids",fourchetteAutourDuPoids); */
    if (fourchetteAutourDuPoids > 1) fourchetteAutourDuPoids = 1;
    if (fourchetteAutourDuPoids < 0.5) fourchetteAutourDuPoids = 0.5;
    show("fourchetteAutourDuPoids",fourchetteAutourDuPoids);
    for (Poisson* p: poissons)
    {
        p->plusGrandTempsDeVie(0);
        p->réseauDeNeurones(survivorFish->réseauDeNeurones());
        p->réseauDeNeurones().poidsAléa(fourchetteAutourDuPoids);
        /* p->réseauDeNeurones().output().poidsAléa(-3.14f,3.14f); */
    }
}

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

    /* RéseauDeNeurones réseauDeNeurones(1,2,8,1); */

    /* réseauDeNeurones.connecteLesLignesEntreElles(); */

    /* réseauDeNeurones.poidsAléa(-3.14f,3.14f); */
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

                if (event.key.code == sf::Keyboard::P)
                {
                    meilleursPoisson()->print();
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
                tauxDeCarnageText.setString( to_string(monde.ticDepuisCréation()/(float)selectionTime ));
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
                    /* requin->angleDeDirection(requin->getAngleEntreMoiEt(requin->prochaineCible())); */

                RéseauDeNeurones::TblValeurs tblValsInput;

                /* size_t i(0); */
                for (Poisson* p: poissons)
                {
                    tblValsInput.clear();
                    for (Requin* requin: requins)
                        tblValsInput.emplace_back(p->getAngleEntreMoiEt(requin));

                    tblValsInput.push_back(p->pos().x/(float)monde.largeur());
                    tblValsInput.push_back(p->pos().y/(float)monde.hauteur());
                    /* tblValsInput.push_back(p->pos().x); */
                    /* tblValsInput.push_back(p->pos().y); */

                    p->tableauxDesValeursEnEntrée(tblValsInput);
                    p->calculeLesValeursDeToutMesNeurones();
                    p->angleDeDirection( p->réseauDeNeurones().output().at(0).valeur() );
                    /* p->angleDeDirection( p->tableauxDesRésultats().at(0)); */
                    /* p->réseauDeNeurones().print(true); */
                }

                monde.tic();

                /* if (monde.ticDepuisCréation() > 0) */
                if (monde.ticDepuisCréation() % selectionTime == selectionTime-1)
                    selectionneEtRepliqueMeilleursPoisson(monde);

                /* requin2->avance(); */

            }
        }

        if (clock.getElapsedTime().asMilliseconds() >= tickTime ) {

            clock.restart();

            // Comme ca je ne redessine pas 2 fois de suite la même image
            if (!iDrawSomething) iDrawSomething = false;

            window.clear(bgColor);


            // Je dessine tout le monde
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


            window.draw(noteText);
            window.draw(tauxDeCarnageText);

            if (iDrawSomething) window.display();
            /* play = false; */

        }
    }

    for (Requin* r: requins)
        delete r;
}
