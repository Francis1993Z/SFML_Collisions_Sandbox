#ifndef ENGINE_HPP_INCLUDED
#define ENGINE_HPP_INCLUDED

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>

#include "RectangleObject.hpp"

struct doubleVector2f
{
    sf::Vector2f v1, v2;
};

class Engine
{
    public:
    Engine(sf::RenderWindow& init_renderwindow);
    void DrawTexts();
    void UpdateRectangleTool(doubleVector2f newdVector2f);
    void UpdateCircleTool(doubleVector2f newdVector2f);
    void DrawRectangleTool();
    void DrawCircleTool();
    void addRectangle();
    void addCircle();
    void DrawRectanglesArray();
    void DrawCirclesArray();
    void DrawDrawablesArray();
    bool Collision(const std::vector<sf::Vector2f> Sommets, sf::Vector2f P);
    void Select(sf::Vector2i c_MousePosition);
    void UpdateUI(sf::Vector2i c_MousePosition, unsigned int c_tool);
    void rotateSelectedObj(float angle);
    sf::Text getText() const;
    bool ToolIsBusy() const;
private:
std::vector<sf::Drawable> DrawablesArray;
std::vector<RectangleObject> RectanlgesArray;
std::vector<sf::CircleShape> CirclesArray;
sf::RectangleShape *rectangletool;
sf::CircleShape *circletool;
sf::Color *future_color;
sf::Font font;
sf::Text text;
sf::RenderWindow *my_renderwindow;
RectangleObject *selected_obj;
};

#endif // ENGINE_HPP_INCLUDED
