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
    RenderWindow window(VideoMode(1280, 720), "Fireboy and Watergirl");
    const int H = 9;
    const int W = 16;
    String TileMap [10] =
    {
    "B              B",
    "B              B",
    "B              B",
    "B              B",
    "B              B",
    "B              B",
    "B              B",
    "B              B",
    "B              B",
    };
    RectangleShape borders[4],rectangle(Vector2f(10,10));
    Vector2f vec(1280,40), vec2(40,720);
    borders[0].setSize(vec), borders[1].setSize(vec2), borders[2].setSize(vec), borders[3].setSize(vec2);
    borders[0].setPosition(0, 0), borders[1].setPosition(0, 0), borders[2].setPosition(0, 680), borders[3].setPosition(1240, 0);
    Texture block;
    block.loadFromFile("assets/block.png");
    borders[0].setTexture(&block),borders[1].setTexture(&block),borders[2].setTexture(&block),borders[3].setTexture(&block);
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
        window.clear();
        int offset = 40;
        for (int i = 0; i < H; i++)
        {
            for (int j = 0; j < W ; j++)
            {
                if (TileMap[i][j] == 'B') rectangle.setFillColor(Color::Blue);
                if (TileMap[i][j] == '0')  rectangle.setFillColor(Color::Green);
                if (TileMap[i][j] == ' ')   continue;
                int h = i * 80 + offset, w = j * 80 + offset;
                if(i == 8)
                    h -= 10;
                if(j == 15)
                    w -= 10;
                rectangle.setPosition(w, h) ;
                window.draw(rectangle);
            }
        }
        for (int i = 0; i < 4; i++) window.draw(borders[i]);

        window.display();
    }

    return 0;
}
