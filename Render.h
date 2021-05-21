#pragma once
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


const int H = 9, W = 16;
void renderBackground()
{
    // Render background
    for (int i = 0; i < 18; i++) {
        for (int j = 0; j < W; j++) {
            int h = i * 40, w = j * 80;
            spriteBackground.setPosition(w, h);
            window.draw(spriteBackground);
        }
    }
}


void renderLevel()
{
    int offset = 40;
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            if (levelsMap[level][i][j] == ' ') continue;
            int h = i * 80 + offset, w = j * 80 + offset;
            if (i == 8) h -= offset;
            if (j == 15) w -= offset;
            spriteStoneMid.setPosition(w, h);
            spriteStoneRight.setPosition(w, h);
            spriteStoneLeft.setPosition(w, h);
            if (levelsMap[level][i][j] == 'M')
                window.draw(spriteStoneMid);
            else if (levelsMap[level][i][j] == 'R')
                window.draw(spriteStoneRight);
            else if (levelsMap[level][i][j] == 'L')
                window.draw(spriteStoneLeft);
        }
    }
}