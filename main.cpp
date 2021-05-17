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

//  Declaring fireBoy and waterGirl sprites and textures
Sprite fireBoy, waterGirl;
Texture fireBoyTexture, waterGirlTexture;

//  Declaring the sprites' velocity variables in both the X and Y directions
float waterGirlVX = 0, waterGirlVY = 0;
float fireBoyVX = 0, fireBoyVY = 0;
float maxSpeed = 3.f;
float gravity = 0.5f, HorizontalPull = 0.5f;
bool motionRightFireBoy = 1, motionRightWaterGirl = 1;

// Functions to update the sprites Y positions taking the velocity in the y direction as a parameter for the move function
void updateWaterGirlPosY()
{
    waterGirl.move({ 0, waterGirlVY });
}

void updateFireBoyPosY()
{
    fireBoy.move({ 0, fireBoyVY });
}

// Functions to update the sprites X positions taking the velocity in the X direction as a parameter for the move function
void updateFireBoyPosX()
{
    fireBoy.move({fireBoyVX, 0});
}

void updateWaterGirlPosX()
{
    waterGirl.move({ waterGirlVX, 0 });
}


int main()
{
    RenderWindow window(VideoMode(1280, 720), "Fireboy and Watergirl", Style::Titlebar | Style::Close);
    window.setFramerateLimit(60);

    const int H = 9, W = 16;

    // Background
    Texture textureBackground;
    textureBackground.loadFromFile("assets/graphics/background.png");

    RectangleShape spriteBackground(Vector2f(80, 40));
    spriteBackground.setTexture(&textureBackground);

    // Level map
    String levelOneMap [5][9] =
            {
                    {"                ",
                     "BBB    BBBBBBBBB",
                     "                ",
                     "BBBBB      BBBBB",
                     "                ",
                     "        BBBBB   ",
                     "                ",
                     "     BBB        ",
                     "                ",
                    },
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
    RectangleShape spriteDirt(Vector2f(80.f, 40.f));
    spriteDirt.setTexture(&textureDirt);

    // Title
    Font fontTitle;
    fontTitle.loadFromFile("assets/fonts/KOMIKAP_.ttf");

    Text textTitle;
    textTitle.setString("Fireboy and Watergirl");
    textTitle.setCharacterSize(70);
    textTitle.setFont(fontTitle);
    textTitle.setFillColor(Color::White);

    FloatRect textRect = textTitle.getLocalBounds();
    textTitle.setOrigin(textRect.left +
                          textRect.width / 2.0f,
                          textRect.top +
                          textRect.height / 2.0f);
    textTitle.setPosition(640, 100);

    // Press enter to start
    Text textStart;
    textStart.setString("Press enter to start");
    textStart.setCharacterSize(50);
    textStart.setFont(fontTitle);
    textStart.setFillColor(Color::White);

    textRect = textStart.getLocalBounds();
    textStart.setOrigin(textRect.left +
                        textRect.width / 2.0f,
                        textRect.top +
                        textRect.height / 2.0f);
    textStart.setPosition(640, 400);

    // Door
    Texture textureDoor;
    textureDoor.loadFromFile("assets/graphics/door.png");

    Sprite spriteDoor;
    spriteDoor.setTexture(textureDoor);
    spriteDoor.setScale(1, 1);
    spriteDoor.setPosition(1160, 560);

    // Fireboy and Watergirl
    fireBoyTexture.loadFromFile("assets/graphics/fireBoy.png"), waterGirlTexture.loadFromFile("assets/graphics/waterGirl.png");
    fireBoy.setTexture(fireBoyTexture), waterGirl.setTexture(waterGirlTexture);
    fireBoy.setPosition({ 41.f, 599.f }), waterGirl.setPosition({ 41.f, 599.f });

    bool gameStarted = false;

    // Main game loop
    while (window.isOpen())
    {
        //GRAVITY AFFECTS CHARACTERS
        if (waterGirl.getPosition().y < 600)
            waterGirlVY += gravity, updateWaterGirlPosY();
        else
            waterGirlVY = 0;
    
        if (fireBoy.getPosition().y < 600)
            fireBoyVY += gravity, updateFireBoyPosY();
        else
            fireBoyVY = 0;

        //DECELERATION EFFECT FOR FIREBOY
        if (motionRightFireBoy && fireBoyVX > 0)
            fireBoyVX -= HorizontalPull, updateFireBoyPosX();
        if (!motionRightFireBoy && fireBoyVX < 0)
            fireBoyVX += HorizontalPull, updateFireBoyPosX();
        
        //DECELERATION EFFECT FOR WATERGIRL
        if (motionRightWaterGirl && waterGirlVX > 0)
            waterGirlVX -= HorizontalPull, updateWaterGirlPosX();
        if (!motionRightWaterGirl && waterGirlVX < 0)
            waterGirlVX += HorizontalPull, updateWaterGirlPosX();

        /*Time time;
        time = clock.restart();

        float iterationsPerSecond = 1.f / time.asSeconds();
        float pixelsPerIteration = maxSpeed / iterationsPerSecond;*/

        if (Keyboard::isKeyPressed(Keyboard::Key::D))
        {
            if (!motionRightWaterGirl)
                motionRightWaterGirl = 1, waterGirlVX = 0;
            waterGirlVX += 1.5 * HorizontalPull;
            if (waterGirlVX > maxSpeed)
                waterGirlVX = maxSpeed;
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::A))
        {
            if (motionRightWaterGirl)
                motionRightWaterGirl = 0, waterGirlVX = 0;
            waterGirlVX -= 1.5 * HorizontalPull;
            if (waterGirlVX < -maxSpeed)
                waterGirlVX = -maxSpeed;
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::Right))
        {
            if (!motionRightFireBoy)
                motionRightFireBoy = 1, fireBoyVX = 0;
            fireBoyVX += 1.5 * HorizontalPull;
            if (fireBoyVX > maxSpeed)
                fireBoyVX = maxSpeed;
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::Left))
        {
            if (motionRightFireBoy)
                motionRightFireBoy = 0, fireBoyVX = 0;
            fireBoyVX -= 1.5 * HorizontalPull;
            if (fireBoyVX < -maxSpeed)
                fireBoyVX = -maxSpeed;
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::W))
        {
            if (waterGirl.getPosition().y == 600 || waterGirl.getPosition().y == 599)
                waterGirlVY = -11, updateWaterGirlPosY();
        
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::Up))
        {
            if (fireBoy.getPosition().y == 600 || fireBoy.getPosition().y == 599)
                fireBoyVY = -11, updateFireBoyPosY();
        }

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed) {
                window.close();
            }
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
                window.close();
            }
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Return) {
                gameStarted = true;
            }
        }

        // Clear
        window.clear();

        // Render background
        for (int i = 0; i < 18; i++) {
            for (int j = 0; j < W; j++) {
                int h = i * 40, w = j * 80;
                spriteBackground.setPosition(w, h);
                window.draw(spriteBackground);
            }
        }


        if (gameStarted)
        {

            // Render level
            int offset = 40;
            for (int l = 0; l < 1; l++)
            {
                for (int i = 0; i < H; i++)
                {
                    for (int j = 0; j < W; j++)
                    {
                        if (levelOneMap[l][i][j] == ' ') continue;
                        int h = i * 80 + offset, w = j * 80 + offset;
                        if (i == 8) h -= offset;
                        if (j == 15) w -= offset;
                        spriteDirt.setPosition(w, h);
                        window.draw(spriteDirt);
                    }
                }
            }


            // Check if fireboy is still inside the drawn borders
            if (fireBoy.getPosition().x < 40)
                fireBoy.setPosition({ 40.f, fireBoy.getPosition().y });
            if (fireBoy.getPosition().x > 1160)
                fireBoy.setPosition({ 1160.f, fireBoy.getPosition().y });
            if (fireBoy.getPosition().y > 600)
                fireBoy.setPosition({ fireBoy.getPosition().x, 600 });

            // Check if watergirl is still inside the drawn borders
            if (waterGirl.getPosition().x < 40)
                waterGirl.setPosition({ 40.f, waterGirl.getPosition().y });
            if (waterGirl.getPosition().x > 1160)
                waterGirl.setPosition({ 1160.f, waterGirl.getPosition().y });
            if (waterGirl.getPosition().y > 600)
                waterGirl.setPosition({ waterGirl.getPosition().x, 600 });

            // Render door
            window.draw(spriteDoor);

            // Render characters
            window.draw(fireBoy);
            window.draw(waterGirl);


            // Render border
            for (int i = 0; i < 4; i++) window.draw(spriteBorder[i]);
        }
        else
        {
            window.draw(textTitle);
            window.draw(textStart);
        }

        window.display();
    }

    return 0;
}
