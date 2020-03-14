#include <SFML/Graphics.hpp>

#include <rnd.hpp>
#include <utils.hpp>
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

unsigned int tickTime = 41; // 24 image/s = 41.66 ms
unsigned short incrTickTime = 2;
unsigned int minTickTime = 2;

vector<sf::Color> colors;
sf::Color bgColor = sf::Color::Black;

bool iDrawSomething = true;

sf::Text noteText;
sf::Clock clockText;
unsigned int textTime = 3;

sf::Text tauxDeCarnageText;
sf::Clock clockTauxDeCarnage;
unsigned int tauxDeCarnageTime = 1;

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
    requin->setDimensionDuMonde(monde.getLargeur(), monde.getHauteur());
    requin->setDimension(30, 30.f);
    /* requin->setDimension(48.540f, 30.f); */
    requin->setCouleur(Couleur(255,0,0));
    Coord posDepart = Coord(monde.getLargeur() / 2 , monde.getHauteur() / 2 );
    requin->setPos(posDepart);
    requin->setMouvant(true);
    requin->setMaxDistanceDeDeplacement(20);
    requin->setMaxAngleDeDirection(0.3f);
    requin->debug();

    /* requin2 = new Requin(); */
    /* requin2->setDimensionDuMonde(monde.getLargeur(), monde.getHauteur()); */
    /* requin2->setDimension(30, 30.f); */
    /* requin2->setCouleur(Couleur(0,0,255)); */
    /* requin2->setPosAléa(); */
    /* requin2->setMouvant(true); */
    /* requin2->setMaxDistanceDeDeplacement(10); */
    /* requin2->setMaxAngleDeDirection(0.3f); */
    /* requin2->debug(); */

    // Je veux des poissons
    unsigned int nombreDePoissons = 1001;
    Couleur clPoisson = Couleur(0,255,0);
    Etre::nbType taillePoisson = 10;

    for (unsigned int i = 0; i < nombreDePoissons; i++)
    {
        Poisson* p = new Poisson();
        p->setDimensionDuMonde(monde.getLargeur(),monde.getHauteur());
        p->setDimension(taillePoisson,taillePoisson);
        p->setPosAléa();
        p->setCouleur(clPoisson);
        p->setMouvant(true);
        p->setMaxDistanceDeDeplacement(requin->getMaxDistanceDeDeplacement() +2);

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

    /* monde.debug(); */

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
                    requin->setNbCiblesMangées(0);
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
                if (event.key.code == sf::Keyboard::Left)
                {
                    requin->setAngleDeDirection(3.14f);
                    requin->avance();
                }
                if (event.key.code == sf::Keyboard::Up)
                {
                    requin->setAngleDeDirection(3.14f*0.5f);
                    requin->avance();
                }
                if (event.key.code == sf::Keyboard::Right)
                {
                    requin->setAngleDeDirection(0.f);
                    requin->avance();
                }
                if (event.key.code == sf::Keyboard::Down)
                {
                    requin->setAngleDeDirection(-3.14f*0.5f);
                    requin->avance();
                }

                if (event.key.code == sf::Keyboard::D)
                {
                    auto bestTempsDeVie = 0;
                    Poisson* meilleurPoisson;
                    for (Poisson* p: poissons)
                    {
                        if (p->m_maxTempsDeVie > bestTempsDeVie) {
                            bestTempsDeVie = p->m_maxTempsDeVie;
                            meilleurPoisson = p;
                        }
                    }
                    show("bestTempsDeVie",bestTempsDeVie);
                    show("var1",meilleurPoisson->m_variablesAléatoires[0]);
                    meilleurPoisson->debug();
                }
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    modeMouseOn = true;
                    requin->setMouvant(false);
                    requin->setPos(event.mouseButton.x,event.mouseButton.y);
                    /* unsigned int xBool = event.mouseButton.x; */
                    /* unsigned int yBool = event.mouseButton.y; */
                }
            }
            if (event.type == sf::Event::MouseButtonReleased)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    modeMouseOn = false;
                    requin->setMouvant(true);
                }
            }

            if (event.type == sf::Event::MouseMoved && modeMouseOn)
            {
                requin->setPos(event.mouseMove.x,event.mouseMove.y);
            }

            if (event.key.code == sf::Keyboard::Add || (event.type == sf::Event::MouseWheelMoved && event.mouseWheel.delta == -1))
            {
                tickTime -= incrTickTime;
                if (tickTime < minTickTime) tickTime = minTickTime;
                notify("tickTime:"+to_string(tickTime)+"ms");
            }
            if (event.key.code == sf::Keyboard::Subtract || (event.type == sf::Event::MouseWheelMoved && event.mouseWheel.delta == 1))
            {
                tickTime += incrTickTime;
                notify("tickTime:"+to_string(tickTime)+"ms");
            }
        }

        if (clockText.getElapsedTime().asSeconds() >= textTime) {
            iDrawSomething = true;
            noteText.setString("");
        }

        if (clockTauxDeCarnage.getElapsedTime().asSeconds() >= tauxDeCarnageTime) {
            iDrawSomething = true;
            tauxDeCarnageText.setString(to_string( requin->getNbCiblesMangées()/clockTotalTime.getElapsedTime().asSeconds() ));
            clockTauxDeCarnage.restart();
        }


        if (clock.getElapsedTime().asMilliseconds() >= static_cast<int>(tickTime) ) {

            clock.restart();

            // Comme ca je ne redessine pas 2 fois de suite la même image
            if (!iDrawSomething) iDrawSomething = false;

            window.clear(bgColor);

            if (play) {

                // Je regarde si le requin à besoin d'une nouvelle cible
                requin->prendLaDirectionDeLaCibleLaPlusProche();
                /* requin2->prendLaDirectionDeLaCibleLaPlusProche(); */
                /* requin->debug(); */
                /* requin->setAngleDeDirection(3*3.14/4); */
                /* show("m_minDistDeLaCibleLaPlusProche",requin->m_minDistDeLaCibleLaPlusProche); */
                requin->avance();
                /* requin2->avance(); */

                for (Poisson* p: poissons)
                {
                    p->calculeNouvelleAngle(p->getAngleEntreMoiEt(requin));
                    p->avance();
                }

            }

            // Je dessine tout le monde
            Etre* etre;
            sf::Color cl;
            Couleur* mcl;
            Etre::nbType posx,posy;
            for (unsigned int i = 0; i < monde.getNbEtres(); i++)
            {
                etre = monde.getEtreNo(i);
                mcl = &etre->getCouleur();
                cl = sf::Color(mcl->r,mcl->g,mcl->b,mcl->a);
                posx = etre->getLeft();
                posy = etre->getTop();

                /* etre->debug(); */
                switch (etre->getForme()) 
                {
                    case Cercle:
                        {
                            sf::CircleShape circle(etre->getLargeur()*0.5f);
                            circle.setFillColor(cl);
                            circle.setPosition(posx , posy);
                            /* circle.setRotation(radToDeg(etre->getAngleDeDirection())); */

                            /* note("pos:"+to_string(pos->x)+","+to_string(pos->y)); */
                            window.draw(circle);
                            iDrawSomething = true;

                            break;
                        }

                    case Rectangle: 
                        {
                            sf::RectangleShape rect(sf::Vector2f(etre->getLargeur(),etre->getHauteur()));
                            rect.setFillColor(cl);
                            rect.setPosition(posx , posy);
                            /* rect.setRotation(-radToDeg(etre->getAngleDeDirection())); */
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
