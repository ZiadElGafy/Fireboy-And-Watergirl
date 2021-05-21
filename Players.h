#pragma once
#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <cstring>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <sftools/Chronometer.hpp>
#include <fstream>
#include "Visuals.h"
using namespace std;
using namespace sf;
using namespace sftools;



int jumpFactor = 42;
int deathCounter = 0;

//Player struct
struct Player
{
    int jumpCnt = jumpFactor, ready = 1, groundCheck = 1;
    Sprite playerSprite;
    //character death
    // Declaring variable to store local bounds
    FloatRect bounds;
    // Declaring variables to store character's x and y coordinates
    float dx, dy;
    //Declaring type (1: fire, 2: water)
    int type;
    //Declaring state (dead or alive)
    bool isDead = 0;
    // Declaring waterGirl or fireBoy sprite for the first time and taking a texture as a parameter
    //Constructor
    Player(Texture& image, int element)
    {
        playerSprite.setTexture(image);
        playerSprite.setPosition({ 41.f, 599.f });
        type = element;
    }
    void Inquire()
    {
        bounds = playerSprite.getGlobalBounds();
        dx = playerSprite.getPosition().x;
        dy = playerSprite.getPosition().y;

        // Checking if waterGirl or fireBoy has collided with a border
        if (dx > 1160)
            playerSprite.setPosition({ 1160, dy });
        if (dx < 40)
            playerSprite.setPosition({ 40, dy });

    }
    void Restart()
    {
        playerSprite.setPosition({ 41.f, 599.f });
        isDead = 0;
    }
    void move(pair < float, float> coordinates)
    {
        playerSprite.move({ coordinates.first,coordinates.second });
    }
    void die()
    {
        isDead = 1;
        playerSprite.setPosition(2000, 2000);
    }
};



// Declaring character death positions
float deathX = -1.f, deathY = -1.f;