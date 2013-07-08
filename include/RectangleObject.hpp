#ifndef RECTANGLEOBJECT_HPP_INCLUDED
#define RECTANGLEOBJECT_HPP_INCLUDED

#include "Object.hpp"

struct AABB
{
  sf::Vector2f A, B , C, D;
};


class RectangleObject : protected Object, public sf::RectangleShape
{
  public:
  RectangleObject(std::string name, sf::Vector2f my_size, sf::Color *future_color, sf::Vector2f my_position, sf::Vector2f my_origin);
 void UpdateRectPoint();

 AABB getRectAABB() const;
  private:
  std::vector<sf::Vector2f> my_Sommets;
  unsigned int Width;
  unsigned int Height;
  float Angle;
  sf::Vector2f Position;
  AABB my_RectAABB;
   std::string my_name;
};

#endif // RECTANGLEOBJECT_HPP_INCLUDED
