#include <iostream>
#include <cstdio>
#include <string>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Engine.hpp"
#include "otherfunc.hpp"

using namespace std;
using namespace sf;



enum outils {RIEN=0, ADD_RECTANGLE=1, ADD_CIRCLE=2};


int main()
{

    bool Run=true;
    RenderWindow App(VideoMode(1024, 768, 32), "SFML");
    Event Event;

    sf::Vector2i localMousePosition;

    App.setFramerateLimit(60);

    Engine engine(App);

    int tools_iterator=0;
    unsigned int my_tool=tools_iterator;
                  cout<<"my_tool : "<<my_tool<<endl;
    doubleVector2f *my_quadvector=NULL;


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
                    /*
                    if (Event.mouseButton.button == sf::Mouse::Left)
                    {
                        //std::cout << "the right button was pressed" << std::endl;
                        //if(my_tool==0) engine.Select(localMousePosition);
                    }
*/
                }//fin MouseButtonPressed

                else if (Event.type == sf::Event::MouseButtonReleased)
                {

                                    switch (my_tool)
                {
                    ///*********************************************************************************///
                case 1://rectangle
                    engine.addRectangle();
                    delete my_quadvector;
                    my_quadvector=NULL;
                break;
                    case 2://circle
                    engine.addCircle();
                    delete my_quadvector;
                    my_quadvector=NULL;
                break;
                  }//fin  switch
                }//fin MouseButtonReleased

                else if (Event.type == sf::Event::MouseWheelMoved)
                {
                    tools_iterator=Event.mouseWheel.delta;
                    if(tools_iterator>0)
                    {
                        if(my_tool==2) my_tool=0;
                        else my_tool++;
                    }
                    else if(tools_iterator<0)
                    {
                         if(my_tool==0) my_tool=2;
                         else my_tool--;
                    }
                    else cout<<"Go home MouseWheel... You're drunk."<<endl;
                }






            }//fin poll.Event()
            sf::Vector2f converted_coord;//la position de la souris est en int
            converted_coord.x=(float)localMousePosition.x;//donc on la convertie en float car Player::Shoot(sf::Vector2f, sf::RenderWindow &myRenderWindow)
            converted_coord.y=(float)localMousePosition.y;//sf::Vector2f est en float

           if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
           {
            engine.rotateSelectedObj(10);
           }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
           {
            engine.rotateSelectedObj(-10);
           }


            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                switch (my_tool)
                {
                    case 0://Selection
                    engine.Select(localMousePosition);
                    break;

                    ///*********************************************************************************///
                case 1://rectangle
                    if(!engine.ToolIsBusy())//Si c'est un nouveau.
                    {
  my_quadvector = new doubleVector2f;
                        my_quadvector->v1=converted_coord;
                        my_quadvector->v2=converted_coord;

                        engine.UpdateRectangleTool(*my_quadvector);
                    }
                    else//Sinon c'est le même.
                    {
  my_quadvector->v2=converted_coord;
 engine.UpdateRectangleTool(*my_quadvector);
                    }
                    break;//fin rectangle
                    ///*********************************************************************************///
                case 2://circle
                    if(!engine.ToolIsBusy())//Si c'est un nouveau.
                    {
                        my_quadvector = new doubleVector2f;
                        my_quadvector->v1=converted_coord;
                        my_quadvector->v2=converted_coord;
                        engine.UpdateCircleTool(*my_quadvector);
                    }
                    else//Sinon c'est le même.
                    {
                        my_quadvector->v2=converted_coord;//bug
                        engine.UpdateCircleTool(*my_quadvector);
                    }
                    break;//fin circle
                    ///*********************************************************************************///
                }//fin switch tool
            }

            if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
            {

                if(!engine.ToolIsBusy())//Si c'est un nouveau.
                {
                    //cout<<"ToolIsBusy() == false"<<endl;

                }
                else//Sinon c'est le même.
                {
                    //cout<<"ToolIsBusy() == true"<<endl;

                }

            }
            engine.UpdateUI(localMousePosition, my_tool);

            App.clear(Color(255,255,255));

            engine.DrawRectanglesArray();
            engine.DrawRectangleTool();
           engine.DrawCirclesArray();
            engine.DrawCircleTool();
            engine.DrawTexts();
            App.display();
        }
    }

    return 0;
}


