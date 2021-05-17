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
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>

using namespace std;
using namespace sf;

int main()
{
    RenderWindow window(VideoMode(1280, 720), "Fireboy and Watergirl", Style::Titlebar | Style::Close);

    const int H = 9;
    const int W = 16;

    // Background
    Texture textureBackground;
    textureBackground.loadFromFile("assets/graphics/background.png");

    RectangleShape spriteBackground(Vector2f(80, 40));
    spriteBackground.setTexture(&textureBackground);


    // Level map
    String levelOneMap [9] =
            {"                ",
             "BBB    BBBBBBBBB",
             "                ",
             "BBBBB      BBBBB",
             "                ",
             "        BBBBB   ",
             "                ",
             "     BBB        ",
             "                ",
            };

    // Border
    Texture textureBorder;
    textureBorder.loadFromFile("assets/graphics/block.png");

    RectangleShape spriteBorder[4];
    Vector2f vec1(1280,40), vec2(40,720);

    spriteBorder[0].setSize(vec1), spriteBorder[1].setSize(vec2);
    spriteBorder[2].setSize(vec1), spriteBorder[3].setSize(vec2);

    spriteBorder[0].setPosition(0, 0), spriteBorder[1].setPosition(0, 0);
    spriteBorder[2].setPosition(0, 680), spriteBorder[3].setPosition(1240, 0);

    spriteBorder[0].setTexture(&textureBorder), spriteBorder[1].setTexture(&textureBorder);
    spriteBorder[2].setTexture(&textureBorder), spriteBorder[3].setTexture(&textureBorder);

    // Dirt
    Texture textureDirt;
    textureDirt.loadFromFile("assets/graphics/dirt.png");

    RectangleShape spriteDirt(Vector2f(80, 40));
    spriteDirt.setTexture(&textureDirt);

    // Main game loop
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed) {
                window.close();
            }
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
                window.close();
            }
        }

        // Clear
        window.clear();

        // Render

        // Render background
        for (int i = 0; i < 18; i++) {
            for (int j = 0; j < W; j++) {
                int h = i * 40, w = j * 80;
                spriteBackground.setPosition(w, h);
                window.draw(spriteBackground);
            }
        }

        // Render level
        int offset = 40;
        for (int i = 0; i < H; i++)
        {
            for (int j = 0; j < W; j++)
            {
                if (levelOneMap[i][j] == ' ') continue;
                int h = i * 80 + offset, w = j * 80 + offset;
                if (i == 8) h -= offset;
                if (j == 15) w -= offset;
                spriteDirt.setPosition(w, h);
                window.draw(spriteDirt);
            }
        }

        // Render border
        for (int i = 0; i < 4; i++) window.draw(spriteBorder[i]);

        // Display
        window.display();
    }

    return 0;
}