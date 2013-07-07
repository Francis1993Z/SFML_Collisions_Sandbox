#include "Engine.hpp"

#include "otherfunc.hpp"

using namespace std;
using namespace sf;

Engine::Engine(sf::RenderWindow& init_renderwindow)
{
    cout<<"init_renderwindow adresse : "<<&init_renderwindow<<endl;
    my_renderwindow=&init_renderwindow;
    cout<<"my_renderwindow valeur : "<<my_renderwindow<<endl;

    if(my_renderwindow!=&init_renderwindow)
    {
        cout<<"ERREUR"<<endl;
    }

    if (!font.loadFromFile("arial.ttf")) cout<<"Ah! Merde alors!"<<endl;
    text.setFont(font);
    text.setCharacterSize(30);
    text.setString("Hello world!");
    text.setColor(sf::Color::Black);
    text.setPosition(0.00f, 0.00f);

    rectangletool=NULL;
}

void Engine::DrawTexts()
{
    my_renderwindow->draw(text);
}

void Engine::UpdateRectangleTool(doubleVector2f newdVector2f)
{

//cout<<"v1.x : "<<newdVector2f.v1.x<<" v1.y : "<<newdVector2f.v1.y<<endl;
//cout<<"v2.x : "<<newdVector2f.v2.x<<" v2.y : "<<newdVector2f.v2.y<<endl;

    float halfwidth=abs(newdVector2f.v1.x-newdVector2f.v2.x);
    float halfheight=abs(newdVector2f.v1.y-newdVector2f.v2.y);

    cout<<"halfwidth : "<<halfwidth<<" halfheight : "<<halfheight<<endl;
    sf::Vector2f mysize;
    mysize.x=(halfwidth*2);
    mysize.y=(halfheight*2);
        //cout<<"UpdateRectangleTool"<<endl;
    if(rectangletool!=NULL)
    {
                //cout<<"UpdateRectangleTool { rectangletool!=NULL }"<<endl;
        delete rectangletool;
        rectangletool=NULL;
        rectangletool = new sf::RectangleShape(mysize);
        rectangletool->setOrigin(halfwidth, halfheight);
        rectangletool->setPosition(newdVector2f.v1);
sf::Color toolcolor=*future_color;
toolcolor.a=150;
        rectangletool->setFillColor(toolcolor);
    }
    else//nouveau
    {
                        //cout<<"UpdateRectangleTool else"<<endl;
        rectangletool = new sf::RectangleShape(mysize);
        rectangletool->setOrigin(halfwidth, halfheight);
        rectangletool->setPosition(newdVector2f.v1);
        int R = rand() % 255 + 50;
        int B = rand() % 255 + 50;
        int G = rand() % 255 + 50;
        future_color = new sf::Color(R,B,G);
        rectangletool->setFillColor(sf::Color(R,G,B));
    }

}

void Engine::UpdateCircleTool(doubleVector2f newdVector2f)
{

  float c_radius=Distance(newdVector2f.v1.x, newdVector2f.v1.y,  newdVector2f.v2.x, newdVector2f.v2.y);
    cout<<"radius : "<<c_radius<<endl;
 sf::Vector2f c_position=newdVector2f.v1;
     cout<<"c_position.x : "<<c_position.x<<"c_position.y : "<<c_position.y<<endl;
 if(circletool!=NULL)
    {
                //cout<<"UpdateRectangleTool { rectangletool!=NULL }"<<endl;
        delete circletool;
        circletool=NULL;
        circletool = new sf::CircleShape(c_radius);
        circletool->setOrigin(c_radius, c_radius);
        circletool->setPosition(c_position);
sf::Color toolcolor=*future_color;
toolcolor.a=150;
        circletool->setFillColor(toolcolor);
    }
    else//nouveau
    {
                        //cout<<"UpdateRectangleTool else"<<endl;
        circletool = new sf::CircleShape(c_radius);
        circletool->setOrigin(c_radius, c_radius);
        circletool->setPosition(c_position);
        int R = rand() % 255 + 50;
        int B = rand() % 255 + 50;
        int G = rand() % 255 + 50;
        future_color = new sf::Color(R,B,G);
        circletool->setFillColor(sf::Color(R,G,B));
    }
}

void Engine::DrawRectangleTool()
{
    if(rectangletool!=NULL)
    {
        //cout<<"DrawRectangleTool"<<endl;
        my_renderwindow->draw(*rectangletool);
    }
}

void Engine::DrawCircleTool()
{
    if(circletool!=NULL)
    {
        //cout<<"DrawCircleTool"<<endl;
        my_renderwindow->draw(*circletool);
    }
}

void Engine::DrawRectanglesArray()
{
 if(!RectanlgesArray.empty())
 {
     for(unsigned int i=0;i<RectanlgesArray.size();i++)
     {
         my_renderwindow->draw(RectanlgesArray.at(i));
     }
 }
}

void Engine::DrawCirclesArray()
{
 if(!CirclesArray.empty())
 {
     for(unsigned int i=0;i<CirclesArray.size();i++)
     {
         my_renderwindow->draw(CirclesArray.at(i));
     }
 }
}

void Engine::addRectangle()
{
    //cout<<"addRectangle"<<endl;

    sf::Vector2f newrectangle_position;
    newrectangle_position.x = rectangletool->getPosition().x;
    newrectangle_position.y = rectangletool->getPosition().y;

    sf::Vector2f newrectangle_size;
    newrectangle_size.x = rectangletool->getSize().x;
    newrectangle_size.y = rectangletool->getSize().y;

    RectanlgesArray.push_back(sf::RectangleShape(newrectangle_size));
    RectanlgesArray.back().setFillColor(*future_color);
    RectanlgesArray.back().setPosition(newrectangle_position);
    RectanlgesArray.back().setOrigin(newrectangle_size.x/2, newrectangle_size.y/2);

    delete rectangletool;
    delete future_color;
    rectangletool=NULL;
    future_color=NULL;

}

void Engine::addCircle()
{
    //cout<<"addRectangle"<<endl;

    sf::Vector2f newcircle_position;
    newcircle_position.x = circletool->getPosition().x;
    newcircle_position.y = circletool->getPosition().y;

    float newcircle_radius;
    newcircle_radius = circletool->getRadius();

    CirclesArray.push_back(sf::CircleShape(newcircle_radius));
    CirclesArray.back().setFillColor(*future_color);
    CirclesArray.back().setPosition(newcircle_position);
    CirclesArray.back().setOrigin(newcircle_radius/2, newcircle_radius/2);

    delete circletool;
    delete future_color;
    circletool=NULL;
    future_color=NULL;

}


bool Engine::ToolIsBusy() const
{
    if(rectangletool!=NULL || circletool!=NULL) return true;
    else return false;
}

sf::Text Engine::getText() const
{
    return text;
}
