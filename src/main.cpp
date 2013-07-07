#include <iostream>
#include <cstdio>
#include <string>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Engine.hpp"

using namespace std;
using namespace sf;

enum outils {RIEN=0, ADD_RECTANGLE=1, ADD_CIRCLE=2};


int main()
{

    bool Run=true;
    RenderWindow App(VideoMode(800, 600, 32), "SFML");
    Event Event;

    sf::Vector2i localMousePosition;

    App.setFramerateLimit(60);

    cout<<"App adresse : "<<&App<<endl;
    Engine engine(App);

    unsigned int tools_iterator=0;
    unsigned int my_tool=tools_iterator;

doubleVector2f *my_quadvector;

    while(Run)
    {

        while(App.isOpen())
        {
            localMousePosition.x=Event.mouseMove.x;
            localMousePosition.y=Event.mouseMove.y;



            while (App.pollEvent(Event))
            {


                if (Event.type == Event::Closed)
                {
                    App.close();
                    Run=false;
                }
                else if (Event.type == Event::MouseMoved)
                {
                    //std::cout << "new mouse x: " << Event.mouseMove.x << std::endl;
                    //std::cout << "new mouse y: " << Event.mouseMove.y << std::endl;
                }

                else if (Event.type == sf::Event::MouseButtonPressed)
                {
                    if (Event.mouseButton.button == sf::Mouse::Right)
                    {
                        //std::cout << "the right button was pressed" << std::endl;
                    }


                        /* switch (my_tool)
                                        {
                                        case RIEN:
                                            cout<<"Nothing to do."<<endl;
                                            break;
                                        case ADD_RECTANGLE:
                                            printf("Salut gamin !");
                                            break;
                                        case ADD_CIRCLE:
                                            printf("Salut jeune !");
                                            break;
                                        default:
                                            printf("Je n'ai aucune phrase de prete pour ton age  ");
                                            break;
                                        }*/


                }//fin MouseButtonPressed

                else if (Event.type == sf::Event::MouseButtonReleased)
                {
                    engine.addRectangle();
                    delete my_quadvector;
                    my_quadvector=NULL;
                }
                else if (Event.type == sf::Event::MouseWheelMoved)
                {
                    std::cout << "wheel movement: " << Event.mouseWheel.delta << std::endl;
                    tools_iterator=Event.mouseWheel.delta;
                    if(tools_iterator>0) my_tool=+tools_iterator;
                    else if(tools_iterator<0) my_tool=-tools_iterator;
                    else cout<<"Go home MouseWheel... You're drunk."<<endl;
                }






            }//fin poll.Event()

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                               sf::Vector2f converted_coord;//la position de la souris est en int
                converted_coord.x=(float)localMousePosition.x;//donc on la convertie en float car Player::Shoot(sf::Vector2f, sf::RenderWindow &myRenderWindow)
                converted_coord.y=(float)localMousePosition.y;//sf::Vector2f est en float
cout<<"Mouse::Left"<<endl;
                if(!engine.ToolIsBusy())//Si c'est un nouveau.
                {
                    cout<<"ToolIsBusy() == false"<<endl;
                my_quadvector = new doubleVector2f;
                my_quadvector->v1=converted_coord;
                my_quadvector->v2=converted_coord;
                                engine.UpdateRectangleTool(*my_quadvector);
                }
                else//Sinon c'est le même.
                {
                    cout<<"ToolIsBusy() == true"<<endl;
                my_quadvector->v2=converted_coord;
                                engine.UpdateRectangleTool(*my_quadvector);
                }

            }

 if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
            {

                if(!engine.ToolIsBusy())//Si c'est un nouveau.
                {
                    cout<<"ToolIsBusy() == false"<<endl;

                }
                else//Sinon c'est le même.
                {
                    cout<<"ToolIsBusy() == true"<<endl;

                }

            }

            App.clear(Color(255,255,255));
            engine.DrawTexts();
            engine.DrawRectangleTool();

            App.display();
        }
    }

    return 0;
}

