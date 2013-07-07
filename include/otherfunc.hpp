#ifndef OTHERFUNC_HPP_INCLUDED
#define OTHERFUNC_HPP_INCLUDED

#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


inline float Distance(float, float, float, float);
inline float Distance_v2f(sf::Vector2f, sf::Vector2f);
inline float GetAngle(float, float, float, float);
inline float GetAngle_v2f(sf::Vector2f, sf::Vector2f);

#endif // OTHERFUNC_HPP_INCLUDED
