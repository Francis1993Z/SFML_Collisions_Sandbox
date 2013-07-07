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
    void DrawRectangleTool();
    void addRectangle();
    void DrawRectanglesArray();
    sf::Text getText() const;
    bool ToolIsBusy() const;
private:
std::vector<sf::RectangleShape> RectanlgesArray;
std::vector<sf::CircleShape> CirclesArray;
sf::RectangleShape *rectangletool;
sf::Color *future_color;
sf::Font font;
sf::Text text;
sf::RenderWindow *my_renderwindow;
};

#endif // ENGINE_HPP_INCLUDED
