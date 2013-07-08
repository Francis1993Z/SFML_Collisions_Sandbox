#include "Engine.hpp"
#include <sstream>

#include "otherfunc.hpp"

using namespace std;
using namespace sf;

inline float Distance(float TheObj_X, float TheObj_Y, float MyObj_X, float MyObj_Y)
{
    float TCoteopposer=MyObj_Y-TheObj_Y;
    float TCoteadjacent=MyObj_X-TheObj_X;
    float Tracinecarre=pow(TCoteadjacent,2)+pow(TCoteopposer,2);
    float Thypothenuse=sqrt(Tracinecarre);

    return Thypothenuse;
}

string floattostring(float f)
{
    ostringstream os;
    os << f;
    return os.str();
}

bool check_bools_F(const std::vector<bool> var)
{
            for(unsigned int i=0; i<var.size(); i++)
    {
  if(var.at(i)!=false) return false;
    }
    return true;
}

Engine::Engine(sf::RenderWindow& init_renderwindow)
{

    my_renderwindow=&init_renderwindow;

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
    circletool=NULL;
    selected_obj=NULL;
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

    sf::Vector2f c_position=newdVector2f.v1;

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
        for(unsigned int i=0; i<RectanlgesArray.size(); i++)
        {
            my_renderwindow->draw(RectanlgesArray.at(i));
        }
    }
}

void Engine::DrawCirclesArray()
{
    if(!CirclesArray.empty())
    {
        for(unsigned int i=0; i<CirclesArray.size(); i++)
        {
            my_renderwindow->draw(CirclesArray.at(i));
        }
    }
}

void Engine::DrawDrawablesArray()
{
    if(!DrawablesArray.empty())
    {
        for(unsigned int i=0; i<DrawablesArray.size(); i++)
        {
            my_renderwindow->draw(DrawablesArray.at(i));
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
    unsigned int nb_rectangle=RectanlgesArray.size();
    std::string new_name;
    std::string num = static_cast<ostringstream*>( &(ostringstream() << nb_rectangle) )->str();
    new_name="Rectangle";
    sf::Vector2f Origin;
    Origin.x=newrectangle_size.x/2;
    Origin.y=newrectangle_size.y/2;
    RectanlgesArray.push_back(RectangleObject(new_name, newrectangle_size, future_color, newrectangle_position, Origin));

//DrawablesArray.push_back(RectanlgesArray.back());
//my_renderwindow->draw(RectanlgesArray.back());
    delete rectangletool;
    delete future_color;
    rectangletool=NULL;
    future_color=NULL;

}

void Engine::addCircle()
{

    sf::Vector2f newcircle_position;
    newcircle_position.x = circletool->getPosition().x;
    newcircle_position.y = circletool->getPosition().y;

    float newcircle_radius;
    newcircle_radius = circletool->getRadius();

    CirclesArray.push_back(sf::CircleShape(newcircle_radius));
    CirclesArray.back().setFillColor(*future_color);
    CirclesArray.back().setPosition(newcircle_position);
    CirclesArray.back().setOrigin(newcircle_radius, newcircle_radius);
//DrawablesArray.push_back(CirclesArray.back());
//my_renderwindow->draw(CirclesArray.back());
    delete circletool;
    delete future_color;
    circletool=NULL;
    future_color=NULL;

}

bool Engine::Collision(const std::vector<sf::Vector2f> Sommets, sf::Vector2f P)
{
//std::cout<<""<<std::endl;

    int nbp=Sommets.size();
    for(int i=0; i<nbp; i++)
    {

        sf::Vector2f A = Sommets.at(i);
        sf::Vector2f B;
        if (i==nbp-1)  // si c'est le dernier point, on relie au premier
            B = Sommets.at(0);
        else           // sinon on relie au suivant.
            B = Sommets.at(i+1);
        sf::Vector2f D,T;
        D.x = B.x - A.x;
        D.y = B.y - A.y;
        T.x = P.x - A.x;
        T.y = P.y - A.y;
//std::cout<<"D.x : "<<D.x<<" T.y : "<<T.y<<std::endl;
//std::cout<<"D.y : "<<D.y<<" T.x : "<<T.x<<std::endl;
        float d = D.x*T.y - D.y*T.x;
        //std::cout<<"d : "<<d<<std::endl;
        if (d>0) return false;  // un point à droite et on arrête tout.
    }
    return true;  // si on sort du for, c'est qu'aucun point n'est à gauche, donc c'est bon.

}

void Engine::Select(sf::Vector2i c_MousePosition)
{
    sf::Vector2f converted_coord;//la position de la souris est en int
    converted_coord.x=(float)c_MousePosition.x;//donc on la convertie en float car Player::Shoot(sf::Vector2f, sf::RenderWindow &myRenderWindow)
    converted_coord.y=(float)c_MousePosition.y;//sf::Vector2f est en float
    //std::cout<<"converted_coord.x : "<<converted_coord.x<<" converted_coord.y : "<<converted_coord.y<<std::endl;


        std::vector<bool> collision;

    for(unsigned int i=0; i<RectanlgesArray.size(); i++)
    {

RectanlgesArray.at(i).UpdateRectPoint();
        AABB tmp_rect=RectanlgesArray.at(i).getRectAABB();
        std::vector<sf::Vector2f> c;

               c.push_back(tmp_rect.D);
               c.push_back(tmp_rect.C);
             c.push_back(tmp_rect.B);
        c.push_back(tmp_rect.A);


        if(Collision(c, converted_coord) == true)
        {
            //cout<<"Oui"<<endl;
            selected_obj=&RectanlgesArray.at(i);

            //cout<<"&RectanlgesArray.at(i) : "<<&RectanlgesArray.at(i)<<endl;
            //cout<<"selected_obj : "<<selected_obj<<endl;

                         bool c=true;

collision.push_back(c);
        }
        else
    {
             bool c=false;
collision.push_back(c);
    }

    }//fin for
    if(check_bools_F(collision) == true) selected_obj=NULL;


}

void Engine::UpdateUI(sf::Vector2i c_MousePosition, unsigned int c_tool)
{

        sf::Vector2f converted_coord;//la position de la souris est en int
    converted_coord.x=(float)c_MousePosition.x;//donc on la convertie en float car Player::Shoot(sf::Vector2f, sf::RenderWindow &myRenderWindow)
    converted_coord.y=(float)c_MousePosition.y;//sf::Vector2f est en float
std::string a_tool;
if(c_tool==0) a_tool="Selection";
else if(c_tool==1) a_tool="Rectangle";
else if(c_tool==2) a_tool="Cercle";
    sf::String ui_string;
    if(selected_obj == NULL)
    {
        ui_string=L"Mouse x : "+floattostring(converted_coord.x)+" y : "+floattostring(converted_coord.y)+
                  L"\n Outil : "+a_tool;

    }
    else
    {

//cout<<"else selected_obj : "<<selected_obj<<endl;
        selected_obj->UpdateRectPoint();
        AABB selected_AABB=selected_obj->getRectAABB();
        //std::string name=selected_obj->getName();
        ui_string=L"Mouse x : "+floattostring(converted_coord.x)+" y : "+floattostring(converted_coord.y)+
                  L"\n Rotation : "+floattostring(selected_obj->getRotation())+
                  L"\n Rect1Point.A.x : "+floattostring(selected_AABB.A.x)+L" Rect1Point.A.y : "+floattostring(selected_AABB.A.y)+
                  L"\n Rect1Point.B.x : "+floattostring(selected_AABB.B.x)+L" Rect1Point.B.y : "+floattostring(selected_AABB.B.y)+
                  L"\n Rect1Point.C.x : "+floattostring(selected_AABB.C.x)+L" Rect1Point.C.y : "+floattostring(selected_AABB.C.y)+
                  L"\n Rect1Point.D.x : "+floattostring(selected_AABB.D.x)+L" Rect1Point.D.y : "+floattostring(selected_AABB.D.y);
    }


    text.setString(ui_string);
//sprintf(Rect1Text, "Collision : FALSE\nRotation : %f\nRect1Point.A.x : %f   Rect1Point.A.y : %f\nRect1Point.B.x : %f   Rect1Point.B.y : %f\nRect1Point.C.x : %f    Rect1Point.C.y : %f\nRect1Point.D.x : %f    Rect1Point.D.y : %f", (float)Rect1Angle, (float)Rect1Point.A.x, (float)Rect1Point.A.y, (float)Rect1Point.B.x, (float)Rect1Point.B.y, (float)Rect1Point.C.x, (float)Rect1Point.C.y, (float)Rect1Point.D.x, (float)Rect1Point.D.y);


}
    void Engine::rotateSelectedObj(float angle)
    {
        if(selected_obj!=NULL)
    {

        float a=selected_obj->getRotation();
        selected_obj->setRotation(a+angle);
    }

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
