#include "RectangleObject.hpp"

    RectangleObject::RectangleObject(std::string name, sf::Vector2f my_size, sf::Color *future_color, sf::Vector2f my_position, sf::Vector2f my_origin)
    {

    RectangleObject::setSize(my_size);
    RectangleObject::setFillColor(*future_color);
    RectangleObject::setPosition(my_position);
    RectangleObject::setOrigin(my_origin);


        my_size.x=sf::RectangleShape::getSize().x;
        my_size.y=sf::RectangleShape::getSize().y;
        //std::cout<<"Size.x : "<<sf::RectangleShape::getSize().x<<" Size.y : "<<sf::RectangleShape::getSize().y<<std::endl;
    Width=my_size.x;
    Height=my_size.y;
    Angle=RectangleObject::getRotation();
    Position=RectangleObject::getPosition();
    my_name=name;
    RectangleObject::UpdateRectPoint();
    }

void RectangleObject::UpdateRectPoint()
{

        Angle=RectangleObject::getRotation();
        Position=RectangleObject::getPosition();
        //std::cout<<"Position.x : "<<Position.x<<" Position.y : "<<Position.y<<std::endl;
        //std::cout<<"Angle : "<<Angle<<std::endl;

    float hs,ls,hc,lc;
	{
		float c=cosf(-Angle*M_PI/180);	// s et c sont définis dans l'accolade donc sont détruites lorsqu'on en sort
		float s=sinf(-Angle*M_PI/180); // car ne nous servent plus
        //std::cout<<"c : "<<c<<" s : "<<s<<std::endl;
		hs=Height*s/2;
		ls=Width*s/2;
		hc=Height*c/2;
		lc=Width*c/2;


        /*std::cout<<"hs : "<<hs<<" ls : "<<ls<<std::endl;
        std::cout<<"hc : "<<hs<<" lc : "<<lc<<std::endl;*/

	}

	float x=Position.x;
	float y=Position.y;

       //std::cout<<"x : "<<x<<" y : "<<y<<std::endl;
	// Ecriture des résultats aux adresses données en paramètre
	my_RectAABB.A.x = x- lc - hs; // x - largeur*cos(angle)/2 - hauteur*sin(angle)/2
	my_RectAABB.B.x = x+ lc - hs; // x + largeur*cos(angle)/2 - hauteur*sin(angle)/2
	my_RectAABB.C.x = x+lc + hs; // x + largeur*cos(angle)/2 + hauteur*sin(angle)/2
	my_RectAABB.D.x = x-lc + hs; // x - largeur*cos(angle)/2 + hauteur*sin(angle)/2

	my_RectAABB.A.y = y- hc + ls; // y + hauteur*cos(angle)/2 - largeur*sin(angle)/2 échanger les signe
	my_RectAABB.B.y =  y-hc - ls; // y + hauteur*cos(angle)/2 + largeur*sin(angle)/2
	my_RectAABB.C.y = y+hc - ls; // y - hauteur*cos(angle)/2 + largeur*sin(angle)/2
	my_RectAABB.D.y = y+hc + ls; // y - hauteur*cos(angle)/2 - largeur*sin(angle)/2
/*
    std::cout<<"my_RectAABB.A.x : "<<my_RectAABB.A.x<<std::endl;
    std::cout<<"my_RectAABB.B.x : "<<my_RectAABB.B.x<<std::endl;
    std::cout<<"my_RectAABB.C.x : "<<my_RectAABB.C.x<<std::endl;
    std::cout<<"my_RectAABB.D.x : "<<my_RectAABB.D.x<<std::endl;

    std::cout<<"my_RectAABB.A.y : "<<my_RectAABB.A.y<<std::endl;
    std::cout<<"my_RectAABB.B.y : "<<my_RectAABB.B.y<<std::endl;
    std::cout<<"my_RectAABB.C.y : "<<my_RectAABB.C.y<<std::endl;
    std::cout<<"my_RectAABB.D.y : "<<my_RectAABB.D.y<<std::endl;
*/
}

AABB RectangleObject::getRectAABB() const
{
    return my_RectAABB;
}

