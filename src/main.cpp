#include <SFML/Graphics.hpp>

#include <rnd.hpp>
#include <displayer.hpp>
using namespace displayer;

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

int tickTime = 3; // 24 image/s = 41.66 ms
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
int tempsDuMonde = 1; // en millisecond
int incrTempsDuMonde = 1;
int minTempsDuMonde = 0;

enum Mode
{
    TEMPS_DU_MONDE,
    TEMPS_AFFICHAGE
};
Mode mode = TEMPS_DU_MONDE;

Requin* requin;
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

    // Je veux un requin
    requin = new Requin();
    requin->dimensionDuMonde(monde.largeur(), monde.hauteur());
    requin->dimension(30, 30.f);
    /* requin->dimension(48.540f, 30.f); */
    requin->couleur(Couleur(255,0,0));
    Coord posDepart = Coord(monde.largeur() / 2 , monde.hauteur() / 2 );
    requin->pos(posDepart);
    requin->maxDistanceDeDéplacement(1);
    requin->maxAngleDeDirection(0.3f);
    requin->print();

    /* requin2 = new Requin(); */
    /* requin2->dimensionDuMonde(monde.largeur(), monde.hauteur()); */
    /* requin2->dimension(30, 30.f); */
    /* requin2->couleur(Couleur(0,0,255)); */
    /* requin2->posAléa(); */
    /* requin2->maxDistanceDeDéplacement(10); */
    /* requin2->maxAngleDeDirection(0.3f); */
    /* requin2->print(); */

    // Je veux des poissons
    unsigned int nombreDePoissons = 1;
    Couleur clPoisson = Couleur(0,255,0);
    Etre::nbType taillePoisson = 10;

    for (unsigned int i = 0; i < nombreDePoissons; i++)
    {
        Poisson* p = new Poisson();
        p->dimensionDuMonde(monde.largeur(),monde.hauteur());
        p->dimension(taillePoisson,taillePoisson);
        p->posAléa();
        p->couleur(clPoisson);
        p->maxDistanceDeDéplacement(requin->maxDistanceDeDéplacement() );

        poissons.push_back(p);
        monde.ajouteEtre(p);
        requin->ajouteCible(p); // héhéhéé
        /* requin2->ajouteCible(p); */
    }

    // j'ajoute le requin dans le monde
    // (en dernier pour qu'il soit dessiner sur les poissons
    monde.ajouteEtre(requin);
    /* monde.ajouteEtre(requin2); */

    note("Création du monde avec leurs habitants TERMINÉ");

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

    /* RéseauDeNeurones réseauDeNeurones(2,2,5,1); */
    /* réseauDeNeurones.ajouteUnHiddenLayer(10); */

    /* réseauDeNeurones.connecteLesLignesEntreElles(); */

    /* réseauDeNeurones.poidsAléa(-3.14f,3.14f); */
    /* réseauDeNeurones.output().poidsAléa(0,1); */

    /* réseauDeNeurones.input().at(0)->valeur(2); */
    /* réseauDeNeurones.input().at(1)->valeur(-3); */
    
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
    font.loadFromFile("/home/pi/.scripts/termine/maths/apprentissage/rsc/NotoMono-Regular.ttf");
    noteText.setFont(font);
    noteText.setCharacterSize(17);
    noteText.setFillColor(sf::Color::Yellow);
    noteText.setPosition(10,10);
    noteText.setStyle( sf::Text::Bold );

    tauxDeCarnageText.setFont(font);
    tauxDeCarnageText.setCharacterSize(17);
    tauxDeCarnageText.setFillColor(sf::Color::Yellow);
    tauxDeCarnageText.setPosition(windowWidth - 70,10);
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
                    requin->nbCiblesMangées(0);
                    clockTotalTime.restart();
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
                    requin->angleDeDirection(3.14f);
                    requin->avance();
                }
                if (event.key.code == sf::Keyboard::Up)
                {
                    requin->angleDeDirection(3.14f*0.5f);
                    requin->avance();
                }
                if (event.key.code == sf::Keyboard::Right)
                {
                    requin->angleDeDirection(0.f);
                    requin->avance();
                }
                if (event.key.code == sf::Keyboard::Down)
                {
                    requin->angleDeDirection(-3.14f*0.5f);
                    requin->avance();
                }

                if (event.key.code == sf::Keyboard::D)
                {
                    continue;
                }
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    modeMouseOn = true;
                    requin->mouvant(false);
                    requin->pos(event.mouseButton.x,event.mouseButton.y);
                    /* unsigned int xBool = event.mouseButton.x; */
                    /* unsigned int yBool = event.mouseButton.y; */
                }
            }
            if (event.type == sf::Event::MouseButtonReleased)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    modeMouseOn = false;
                    requin->mouvant(true);
                }
            }

            if (event.type == sf::Event::MouseMoved && modeMouseOn)
            {
                requin->pos(event.mouseMove.x,event.mouseMove.y);
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
            tauxDeCarnageText.setString(to_string( requin->nbCiblesMangées()/clockTotalTime.getElapsedTime().asSeconds() ));
            clockTauxDeCarnage.restart();
        }

        if (clockDuMonde.getElapsedTime().asMilliseconds() >= tempsDuMonde)
        {
            clockDuMonde.restart();
            if (play) 
            {

                // TODO faire en sorte que ce soit le monde qui avant d'un pas plutot que chaque être ici

                // Je regarde si le requin à besoin d'une nouvelle cible
                /* requin->prendLaDirectionDeLaCibleLaPlusProche(); */
                requin->angleDeDirection(requin->getAngleEntreMoiEt(requin->prochaineCible()));
                /* show("angleDeDirection",requin->angleDeDirection()); */
                requin->avance();
                /* requin2->avance(); */

                /* for (Poisson* p: poissons) */
                /* { */
                /*     p->avance(); */
                /* } */

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
                etre = monde.getEtreNo(i);
                mcl = &etre->couleur();
                cl = sf::Color(mcl->r,mcl->g,mcl->b,mcl->a);
                posx = etre->getLeft();
                posy = etre->getTop();

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

    delete requin;
}
