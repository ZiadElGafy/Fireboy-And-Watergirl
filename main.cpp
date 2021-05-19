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
#include <sftools/Chronometer.hpp>
#include <fstream>
using namespace std;
using namespace sf;
using namespace sftools;

//  /Users/pluto/Desktop/Fireboy-And-Watergirl/

// decraing text strings
string introText = "";

// loading intro text
void loadText()
{
    string temp;
    ifstream introFile;
    introFile.open("assets/textData/introText.txt");

    if (!introFile.fail())
    {
        while (!introFile.eof())
        {
            getline(introFile, temp);
            introText += temp;
            introText += '\n';
        };
    }
}


//  Declaring fireBoy and waterGirl sprites and textures

string m = "/Users/pluto/Desktop/Fireboy-And-Watergirl/";
int jumpFactor = 40;
float gravity = 6.5;
Texture fireBoyTexture, waterGirlTexture;
class Player
{
public:
    int jumpCnt = jumpFactor, ready = 1, groundCheck = 1;
    Sprite playerSprite;
    // Declaring variable to store local bounds
    FloatRect bounds;
    // Declaring variables to store character's x and y coordinates
    float dx, dy;
    // Declaring waterGirl or fireBoy sprite for the first time and taking a texture as a parameter
    Player(Texture &image)
    {
        playerSprite.setTexture(image);
        playerSprite.setPosition({ 41.f, 599.f });

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
            playerSprite.setPosition({ 40, dy});

    }
    void Restart()
    {
        playerSprite.setPosition({ 41.f, 599.f });
    }
    void move( pair < float, float> coordinates)
    {
        playerSprite.move({coordinates.first,coordinates.second});
    }
};

int main()
{
    RenderWindow window(VideoMode(1280, 720), "Fireboy and Watergirl", Style::Titlebar | Style::Close);
    window.setFramerateLimit(60);

    // Declaring characters
    fireBoyTexture.loadFromFile("assets/graphics/fireBoy.png");
    waterGirlTexture.loadFromFile("assets/graphics/waterGirl.png");
    Player fireBoy(fireBoyTexture), waterGirl(waterGirlTexture);

    const int H = 9, W = 16;
    // Background
    Texture textureBackground;
    textureBackground.loadFromFile("assets/graphics/backGroundBrick.png");

    RectangleShape spriteBackground(Vector2f(80, 40));
    spriteBackground.setTexture(&textureBackground);

    // Levels map
    String levelsMap [5][9] =
            {
                    // Level one
                    {
                            "                ",
                            "                ",
                            "            LMMR",
                            "          M     ",
                            "        M       ",
                            "      M         ",
                            "    M           ",
                            "  M             ",
                            "                ",
                    },
            };

    // Creating Objects for platforms
    Color color(255, 255, 255, 100);
    vector<RectangleShape> platformObjects;
    int streak = 0;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            if (levelsMap[0][i][j] != ' ')
            {
                streak++;
            }
            else
            {
                if (streak)
                {
                    float start = (j - streak) * 80 + 40, end = start+(80*streak);
                    RectangleShape obj({end-start, 40});
                    obj.setPosition({start, (float)(40 + 80 * i) });
                    obj.setFillColor(color);
                    platformObjects.push_back(obj);
                    streak = 0;
                }
            }
        }
        if(streak)
        {
            float start = (15 - streak) * 80 + 40 + 80, end = start + (80 * streak);
            RectangleShape obj({ end - start, 40 });
            obj.setPosition({ start, (float)(40 + 80 * i) });
            obj.setFillColor(color);
            platformObjects.push_back(obj);
            streak = 0;
        }
    }

    RectangleShape ground({ 1280, 1 });
    ground.setPosition({ 0, 680 });
    platformObjects.push_back(ground);

    // Borders
    Texture textureSideBorder, textureBottomBorder, textureTopBorder;
    textureTopBorder.loadFromFile("assets/graphics/topBorder.png");
    textureSideBorder.loadFromFile("assets/graphics/sideBorder.png");
    textureBottomBorder.loadFromFile("assets/graphics/bottomBorder.png");

    // 0 -> Top border, 1 -> Bottom border, 2 -> Left border, 3 -> Right border
    RectangleShape borders[4];

    Vector2f vec1(1280,40), vec2(40,720);

    borders[2].setSize(vec2), borders[3].setSize(vec2);
    borders[0].setSize(vec1), borders[1].setSize(vec1);

    borders[2].setPosition(0, 0), borders[3].setPosition(1240, 0);
    borders[0].setPosition(0, 0), borders[1].setPosition(0, 680);

    borders[2].setTexture(&textureSideBorder), borders[3].setTexture(&textureSideBorder);
    borders[0].setTexture(&textureTopBorder), borders[1].setTexture(&textureBottomBorder);

    // Stones
    Texture textureStoneMid;
    textureStoneMid.loadFromFile("assets/graphics/stoneMid.png");
    RectangleShape spriteStoneMid(Vector2f(80.f, 40.f));
    spriteStoneMid.setTexture(&textureStoneMid);

    Texture textureStoneLeft;
    textureStoneLeft.loadFromFile("assets/graphics/stoneLeft.png");
    RectangleShape spriteStoneLeft(Vector2f(80.f, 40.f));
    spriteStoneLeft.setTexture(&textureStoneLeft);

    Texture textureStoneRight;
    textureStoneRight.loadFromFile( "assets/graphics/stoneRight.png");
    RectangleShape spriteStoneRight(Vector2f(80.f, 40.f));
    spriteStoneRight.setTexture(&textureStoneRight);

    // Title
    Font fontTitle;
    fontTitle.loadFromFile("assets/fonts/KOMIKAP_.ttf");

    Text textTitle;
    textTitle.setFont(fontTitle);
    textTitle.setCharacterSize(70);
    textTitle.setFillColor(Color::White);
    textTitle.setString("Fireboy and Watergirl");

    FloatRect textRect = textTitle.getLocalBounds();
    textTitle.setOrigin(textRect.left +
                        textRect.width / 2.0f,
                        textRect.top +
                        textRect.height / 2.0f);
    textTitle.setPosition(640, 100);

    // Intro text
    loadText();
    Text textIntro;
    textIntro.setFont(fontTitle);
    textIntro.setCharacterSize(30);
    textIntro.setFillColor(Color::White);
    textIntro.setString(introText);

    textRect = textIntro.getLocalBounds();
    textIntro.setOrigin(textRect.left +
                        textRect.width / 2.0f,
                        textRect.top +
                        textRect.height / 2.0f);
    textIntro.setPosition(640, 200);

    // Pause background
    Texture texturePauseBackground;
    texturePauseBackground.loadFromFile("assets/graphics/pauseBackground.png");

    Sprite spritePauseBackground;
    spritePauseBackground.setTexture(texturePauseBackground);
    spritePauseBackground.setPosition(0, 0);

    // Paused
    Text textPaused;
    textPaused.setFont(fontTitle);
    textPaused.setCharacterSize(70);
    textPaused.setFillColor(Color::White);
    textPaused.setString("Paused");

    textRect = textPaused.getLocalBounds();
    textPaused.setOrigin(textRect.left +
                         textRect.width / 2.0f,
                         textRect.top +
                         textRect.height / 2.0f);
    textPaused.setPosition(640, 100);

    // Start
    Text textStart;
    textStart.setFont(fontTitle);
    textStart.setCharacterSize(50);
    textStart.setFillColor(Color::White);
    textStart.setString("Press enter to start");

    textRect = textStart.getLocalBounds();
    textStart.setOrigin(textRect.left +
                        textRect.width / 2.0f,
                        textRect.top +
                        textRect.height / 2.0f);
    textStart.setPosition(640, 400);

    // Main menu
    Text textMainMenu;
    textMainMenu.setFont(fontTitle);
    textMainMenu.setCharacterSize(50);
    textMainMenu.setFillColor(Color::White);
    textMainMenu.setString("Main menu");

    textRect = textMainMenu.getLocalBounds();
    textMainMenu.setOrigin(textRect.left +
                           textRect.width / 2.0f,
                           textRect.top +
                           textRect.height / 2.0f);
    textMainMenu.setPosition(640, 600);

    // Retry level
    Text textRetryLevel;
    textRetryLevel.setFont(fontTitle);
    textRetryLevel.setCharacterSize(50);
    textRetryLevel.setFillColor(Color::White);
    textRetryLevel.setString("Retry Level");

    textRect = textMainMenu.getLocalBounds();
    textRetryLevel.setOrigin(textRect.left +
                             textRect.width / 2.0f,
                             textRect.top +
                             textRect.height / 2.0f);
    textRetryLevel.setPosition(610, 400);

    // Continue
    Text textContinue;
    textContinue.setFont(fontTitle);
    textContinue.setCharacterSize(50);
    textContinue.setFillColor(Color::White);
    textContinue.setString("Press escape to continue");

    textRect = textContinue.getLocalBounds();
    textContinue.setOrigin(textRect.left +
                           textRect.width / 2.0f,
                           textRect.top +
                           textRect.height / 2.0f);
    textContinue.setPosition(640, 300);

    // Continue intro
    Text textContinueIntro;
    textContinueIntro.setFont(fontTitle);
    textContinueIntro.setCharacterSize(60);
    textContinueIntro.setFillColor(Color::White);
    textContinueIntro.setString("Press enter to continue");

    textRect = textContinueIntro.getLocalBounds();
    textContinueIntro.setOrigin(textRect.left +
                           textRect.width / 2.0f,
                           textRect.top +
                           textRect.height / 2.0f);
    textContinueIntro.setPosition(640, 430);

    // Exit
    Text textExit;
    textExit.setFont(fontTitle);
    textExit.setString("Exit");
    textExit.setCharacterSize(50);
    textExit.setFillColor(Color::White);

    textRect = textExit.getLocalBounds();
    textExit.setOrigin(textRect.left +
                       textRect.width / 2.0f,
                       textRect.top +
                       textRect.height / 2.0f);
    textExit.setPosition(1200, 680);

    // Settings
    Text textSettings;
    textSettings.setFont(fontTitle);
    textSettings.setString("Settings");
    textSettings.setCharacterSize(50);
    textSettings.setFillColor(Color::White);

    textRect = textSettings.getLocalBounds();
    textSettings.setOrigin(textRect.left +
                           textRect.width / 2.0f,
                           textRect.top +
                           textRect.height / 2.0f);
    textSettings.setPosition(640, 500);

    Text textOn;
    textOn.setFont(fontTitle);
    textOn.setString("On");
    textOn.setCharacterSize(50);
    textOn.setFillColor(Color::White);
    textRect = textOn.getLocalBounds();
    textOn.setOrigin(textRect.left +
                     textRect.width / 2.0f,
                     textRect.top +
                     textRect.height / 2.0f);
    textOn.setPosition(640, 300);

    Text textOff;
    textOff.setFont(fontTitle);
    textOff.setString("Off");
    textOff.setCharacterSize(50);
    textOff.setFillColor(Color::White);
    textRect = textOff.getLocalBounds();
    textOff.setOrigin(textRect.left +
                      textRect.width / 2.0f,
                      textRect.top +
                      textRect.height / 2.0f);
    textOff.setPosition(640, 500);

    Text textMusic;
    textMusic.setFont(fontTitle);
    textMusic.setString("Music: ");
    textMusic.setCharacterSize(50);
    textMusic.setFillColor(Color::White);
    textRect = textMusic.getLocalBounds();
    textMusic.setOrigin(textRect.left +
                        textRect.width / 2.0f,
                        textRect.top +
                        textRect.height / 2.0f);
    textMusic.setPosition(620, 300);

    Text textSoundFx;
    textSoundFx.setFont(fontTitle);
    textSoundFx.setString("Sound Fx: ");
    textSoundFx.setCharacterSize(50);
    textSoundFx.setFillColor(Color::White);
    textRect = textSoundFx.getLocalBounds();
    textSoundFx.setOrigin(textRect.left +
                          textRect.width / 2.0f,
                          textRect.top +
                          textRect.height / 2.0f);
    textSoundFx.setPosition(620, 400);

    Texture textureWhiteArrow, textureRedArrow;
    textureRedArrow.loadFromFile("assets/graphics/redArrow.png");
    textureWhiteArrow.loadFromFile("assets/graphics/whiteArrow.png");

    RectangleShape arrow;
    arrow.setSize(Vector2f(150,80));
    arrow.setPosition(30,40);
    arrow.setTexture(&textureWhiteArrow);

    // Door
    Texture textureDoor;
    textureDoor.loadFromFile("assets/graphics/door.png");

    Sprite spriteDoor;
    spriteDoor.setTexture(textureDoor);
    spriteDoor.setScale(1, 1);
    spriteDoor.setPosition(1160, 95);


    // Sound effects
    SoundBuffer bufferFireboyJump, bufferWatergirlJump, bufferLevelComplete, bufferButtonHover;
    bufferFireboyJump.loadFromFile( "assets/audio/fireboyJump.ogg");
    bufferButtonHover.loadFromFile("assets/audio/buttonHover.ogg");
    bufferWatergirlJump.loadFromFile("assets/audio/watergirlJump.ogg");
    bufferLevelComplete.loadFromFile("assets/audio/levelComplete.ogg");

    Sound soundButtonHover(bufferButtonHover);
    Sound soundLevelComplete(bufferLevelComplete);
    Sound soundFireboyJump(bufferFireboyJump), soundWatergirlJump(bufferWatergirlJump);

    // Music
    Music musicIntro, musicLevel;
    musicIntro.openFromFile( "assets/audio/intro.ogg");
    musicLevel.openFromFile( "assets/audio/level.ogg");
    musicIntro.setLoop(true), musicLevel.setLoop(true);

    musicIntro.setVolume(50);
    musicLevel.setVolume(40);
    soundButtonHover.setVolume(1000);

    // Timer
    Time time;
    Text textTimer;
    stringstream ss;
    Chronometer chron;
    string stringTimer;
    textTimer.setFont(fontTitle);
    textTimer.setPosition(590, 0);
    textTimer.setCharacterSize(35);
    textTimer.setFillColor(Color::White);

    // Flags
    bool paused = false;
    bool started = false;
    bool musicMute = false;
    bool soundFxMute = false;
    bool gameStarted = false;
    bool settingsMenu = false;
    bool hoverExit = false;
    bool hoverStart = false;
    bool hoverArrow = false;
    bool hoverRetry = false;
    bool hoverContinue = false;
    bool hoverContinueIntro = false;
    bool hoverSettings = false;
    bool hoverMainMenu = false;
    bool hoverMusicMute = false;
    bool hoverSoundFxMute = false;
    bool pushedFireBoy = false;
    bool pushedWaterGirl = false;
    bool pressedMusicMute = false;
    bool pressedSoundFxMute = false;
    bool continueFillColorInc = false;

    int continueFillColor = 255;

    Clock clock;
    // Main game loop
    while (window.isOpen())
    {
        // Check continue fill color increasing
        if (!continueFillColor) continueFillColorInc = true;
        else if (continueFillColor == 255) continueFillColorInc = false;

        //Jump cnt increments
        if (fireBoy.jumpCnt < 100) { ++fireBoy.jumpCnt; }
        if (waterGirl.jumpCnt < 100) { ++waterGirl.jumpCnt; }

        //speed and clock calculations
        Time timePerIteration;
        timePerIteration = clock.restart();

        float speed = 150;
        float iterationsPerSecond = 1.f / timePerIteration.asSeconds();
        float pixelsPerIteration = speed / iterationsPerSecond;

        float safe = 5.f;

        //Resistance
        for (auto i : platformObjects)
        {
            waterGirl.Inquire();
            //Y-axis
            if (waterGirl.bounds.intersects(i.getGlobalBounds()))
            {
                waterGirl.jumpCnt = jumpFactor + 1;
                if(waterGirl.dy < i.getPosition().y)
                {
                    pushedWaterGirl = false;
                    waterGirl.move( {0, -gravity} );
                    waterGirl.groundCheck = 1;
                }
            }

            if (fireBoy.bounds.intersects(i.getGlobalBounds()))
            {
                pushedFireBoy = false;
                fireBoy.jumpCnt = jumpFactor + 1;
                if(fireBoy.dy < i.getPosition().y)
                {
                    fireBoy.move({ 0, -gravity });
                    fireBoy.groundCheck = 1;
                }
            }

            //X-axis
            waterGirl.Inquire();
            if (waterGirl.bounds.intersects(i.getGlobalBounds()) && waterGirl.dy + 80 - safe >= i.getPosition().y && waterGirl.dx + 80 - safe >= i.getPosition().x)
            {
                pushedWaterGirl = true;
                waterGirl.move({ pixelsPerIteration, 0 });
            }
            waterGirl.Inquire();
            if (waterGirl.bounds.intersects(i.getGlobalBounds()) && waterGirl.dy + 80 - safe >= i.getPosition().y && waterGirl.dx+ safe <= i.getPosition().x + i.getGlobalBounds().width)
            {
                pushedWaterGirl = true;
                waterGirl.move({ -pixelsPerIteration, 0 });
            }
            fireBoy.Inquire();
            if (fireBoy.bounds.intersects(i.getGlobalBounds()) && fireBoy.dy + 80 - safe >= i.getPosition().y && fireBoy.dx + 80 - safe >= i.getPosition().x)
            {
                pushedFireBoy = true;
                fireBoy.move({ pixelsPerIteration, 0 });
            }
            if (fireBoy.bounds.intersects(i.getGlobalBounds()) && fireBoy.dy + 80 - safe >= i.getPosition().y && fireBoy.dx + safe <= i.getPosition().x + i.getGlobalBounds().width)
            {
                pushedFireBoy = true;
                fireBoy.move({ -pixelsPerIteration, 0 });
            }
        }

        waterGirl.move({ 0, gravity });
        fireBoy.move({ 0, gravity });

        if (Keyboard::isKeyPressed(Keyboard::Key::D) && !paused && gameStarted)
        {
            if (!pushedWaterGirl) waterGirl.move({ pixelsPerIteration , 0});
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::A) && !paused && gameStarted)
        {
            if (!pushedWaterGirl) waterGirl.move({-pixelsPerIteration , 0});
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::Right) && !paused && gameStarted)
        {
            if (!pushedFireBoy) fireBoy.move({ pixelsPerIteration , 0});
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::Left) && !paused && gameStarted)
        {
            if (!pushedFireBoy) fireBoy.move({ -pixelsPerIteration , 0 });
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::W) && !paused && gameStarted)
        {
            if (!pushedWaterGirl && waterGirl.jumpCnt > jumpFactor && waterGirl.ready >= iterationsPerSecond/2 && waterGirl.groundCheck)
            {
                waterGirl.jumpCnt = 0;
                waterGirl.ready = 0;
                waterGirl.groundCheck = 0;
                if(!soundFxMute)
                    soundWatergirlJump.play();
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::Up) && !paused && gameStarted)
        {
            if (!pushedFireBoy && fireBoy.jumpCnt > jumpFactor && fireBoy.ready >= iterationsPerSecond/2 && fireBoy.groundCheck)
            {
                fireBoy.jumpCnt = 0;
                fireBoy.ready = 0;
                fireBoy.groundCheck = 0;
                if(!soundFxMute)
                    soundFireboyJump.play();
            }
        }

        //Jump mechanics
        if (fireBoy.jumpCnt <= jumpFactor)
        {
            fireBoy.move({0, ((fireBoy.jumpCnt - (jumpFactor / 2)) / 2)});
            fireBoy.move({0, -gravity});

        }
        if (waterGirl.jumpCnt <= jumpFactor)
        {
            waterGirl.move({0, (waterGirl.jumpCnt - (jumpFactor / 2)) / 2});
            waterGirl.move({0, -gravity});
        }

        ++waterGirl.ready;
        ++fireBoy.ready;

        //Side Barriers
        waterGirl.Inquire();
        fireBoy.Inquire();

        // Check level music
        if (soundLevelComplete.getStatus() != Music::Status::Playing && musicIntro.getStatus() != Music::Status::Playing && !gameStarted && !musicMute)
            musicIntro.play();

        // Getting elapsed time
        time = chron.getElapsedTime();
        int seconds = time.asSeconds(), minutes = seconds / 60;
        seconds %= 60;

        // Get mouse position
        float mouse_xAxis = Mouse::getPosition(window).x, mouse_yAxis = Mouse::getPosition(window).y;

        // Adding the elapsed time into a string
        if (minutes <= 9)
            ss << 0;
        ss << minutes << ":";
        if (seconds <= 9)
            ss << 0;
        ss << seconds;
        ss >> stringTimer;
        ss.clear();
        textTimer.setString(stringTimer);

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed) {
                window.close();
            }
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape && gameStarted) {
                if(settingsMenu)
                    settingsMenu = false;
                else if (paused)
                    paused = false, chron.resume();
                else
                    paused = true, chron.pause();
            }
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Return) {
                if (!started)
                {
                    started = true;
                    textContinueIntro.setFillColor(Color::White);
                }
                else if (!gameStarted)
                {
                    chron.reset();
                    chron.resume();
                    gameStarted = true;
                    musicIntro.stop();
                    if (musicLevel.getStatus() != Music::Status::Playing)
                        musicLevel.play();
                }
            }
            if(event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left)
            {
                pressedMusicMute = false;
                pressedSoundFxMute = false;
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
            if(musicMute)
                musicLevel.stop();

            // Render door
            window.draw(spriteDoor);

            // Render level
            int offset = 40;
            for (int l = 0; l < 1; l++)
            {
                for (int i = 0; i < H; i++)
                {
                    for (int j = 0; j < W; j++)
                    {
                        if (levelsMap[l][i][j] == ' ') continue;
                        int h = i * 80 + offset, w = j * 80 + offset;
                        if (i == 8) h -= offset;
                        if (j == 15) w -= offset;
                        spriteStoneMid.setPosition(w, h);
                        spriteStoneRight.setPosition(w, h);
                        spriteStoneLeft.setPosition(w, h);
                        if (levelsMap[0][i][j] == 'M')
                            window.draw(spriteStoneMid);
                        else if (levelsMap[0][i][j] == 'R')
                            window.draw(spriteStoneRight);
                        else if (levelsMap[0][i][j] == 'L')
                            window.draw(spriteStoneLeft);
                    }
                }
            }

            // Check if fireboy and Watergirl is still inside the drawn borders
            fireBoy.Inquire();
            waterGirl.Inquire();
            // Render characters
            window.draw(fireBoy.playerSprite);
            window.draw(waterGirl.playerSprite);

            // Render border
            for (int i = 0; i < 4; i++) window.draw(borders[i]);

            // Render timer
            window.draw(textTimer);

            // Level ending
            fireBoy.Inquire(), waterGirl.Inquire();
            if (fireBoy.dx >= 1160 && fireBoy.dy <= 131 && waterGirl.dx >= 1160 && waterGirl.dy <= 131)
            {
                gameStarted = false;
                musicLevel.stop();
                if (!soundFxMute) soundLevelComplete.play();
                fireBoy.Restart();
                waterGirl.Restart();
            }

            // Render pause background
            if (gameStarted && paused)
            {
                window.draw(spritePauseBackground);
            }
        }
        if (!gameStarted && !paused && !settingsMenu && started)
        {
            // Render text title
            window.draw(textTitle);

            // Start button
            if (!gameStarted && mouse_xAxis >= 330 && mouse_xAxis <= 950 && mouse_yAxis >= 378.5 && mouse_yAxis <= 421.5)
            {
                if (!hoverStart)
                {
                    soundButtonHover.play();
                    hoverStart = true;
                }
                textStart.setFillColor(Color::Green);
                if (Mouse::isButtonPressed(Mouse::Left))
                {
                    gameStarted = true;
                    chron.reset(), chron.resume();
                    musicIntro.stop();
                    musicLevel.play();
                }
            }
            else {
                hoverStart = false;
                textStart.setFillColor(Color::White);
            }
            window.draw(textStart);
        }
        if ((paused || !gameStarted) && !settingsMenu && started)
        {
            // Exit button
            if (mouse_xAxis >= 1145 && mouse_xAxis <= 1250 && mouse_yAxis >= 655 && mouse_yAxis <= 705)
            {
                if (!hoverExit)
                {
                    soundButtonHover.play();
                    hoverExit = true;
                }
                textExit.setFillColor(Color::Red);
                if (Mouse::isButtonPressed(Mouse::Left))
                    window.close();
            }
            else {
                hoverExit = false;
                textExit.setFillColor(Color::White);
            }
            window.draw(textExit);

            // Settings Button
            if (mouse_xAxis >= 518 && mouse_xAxis <= 760 && mouse_yAxis >= 483 && mouse_yAxis <= 520)
            {
                if (!hoverSettings)
                {
                    soundButtonHover.play();
                    hoverSettings = true;
                }
                textSettings.setFillColor(Color::Green);
                if (Mouse::isButtonPressed(Mouse::Left))
                    settingsMenu = true;
            }
            else {
                hoverSettings = false;
                textSettings.setFillColor(Color::White);
            }
            window.draw(textSettings);
        }
        if (paused && !settingsMenu && started)
        {
            // Render text paused
            window.draw(textPaused);

            // Continue button
            if (mouse_xAxis >= 278.5 && mouse_xAxis <= 1001.5 && mouse_yAxis >= 278.5 && mouse_yAxis <= 321.5)
            {
                if (!hoverContinue)
                {
                    soundButtonHover.play();
                    hoverContinue = true;
                }
                textContinue.setFillColor(Color::Green);
                if (Mouse::isButtonPressed(Mouse::Left))
                    paused = false, chron.resume();
            }
            else {
                hoverContinue = false;
                textContinue.setFillColor(Color::White);
            }
            window.draw(textContinue);

            // Retry level Button
            if (mouse_xAxis >= 508.5 && mouse_xAxis <= 801.5 && mouse_yAxis >= 378.5 && mouse_yAxis <= 421.5)
            {
                if (!hoverRetry)
                    hoverRetry = true;

                textRetryLevel.setFillColor(Color::Green);
                if (Mouse::isButtonPressed(Mouse::Left))
                {
                    waterGirl.Restart(), fireBoy.Restart();
                    chron.reset(), chron.resume(), paused = false;
                    musicLevel.stop(), musicLevel.play();
                }
            }
            else {
                hoverRetry = false;
                textRetryLevel.setFillColor(Color::White);
            }
            window.draw(textRetryLevel);

            // Main menu button
            if (mouse_xAxis >= 516.5 && mouse_xAxis <= 763.5 && mouse_yAxis >= 578.5 && mouse_yAxis <= 621.5)
            {
                if (!hoverMainMenu)
                {
                    soundButtonHover.play();
                    hoverMainMenu = true;
                }
                textMainMenu.setFillColor(Color::Green);
                if (Mouse::isButtonPressed(Mouse::Left))
                {
                    gameStarted = false, paused = false;
                    fireBoy.Restart(), waterGirl.Restart();
                    musicLevel.stop();
                }
            }
            else {
                hoverMainMenu = false;
                textMainMenu.setFillColor(Color::White);
            }
            window.draw(textMainMenu);
        }
        if (settingsMenu && started)
        {
            Text state1, state2;

            if(musicMute)
                state1 = textOff;
            else
                state1 = textOn;

            if(soundFxMute)
                state2 = textOff;
            else
                state2 = textOn;


            // Music mute button
            if (mouse_xAxis >= 700 && mouse_xAxis <= 780 && mouse_yAxis >= 280 && mouse_yAxis <= 321)
            {
                if (!hoverMusicMute)
                {
                    soundButtonHover.play();
                    hoverMusicMute = true;
                }
                if(musicMute)
                {
                    state1 = textOff;
                    state1.setFillColor(Color::Green);
                }
                else
                {
                    state1 = textOn;
                    state1.setFillColor(Color::Red);
                }
                if (Mouse::isButtonPressed(Mouse::Left) && !pressedMusicMute)
                {
                    if(musicMute)
                    {
                        if (gameStarted) musicLevel.play();
                        else musicIntro.play();
                        musicMute = false;
                    }
                    else
                    {
                        if (gameStarted) musicLevel.stop();
                        else musicIntro.stop();
                        musicMute = true;
                    }
                    pressedMusicMute = true;
                }
            }
            else {
                hoverMusicMute = false;
                state1.setFillColor(Color::White);
            }

            // Sound fx mute button
            if (mouse_xAxis >= 750 && mouse_xAxis <= 810 && mouse_yAxis >= 376 && mouse_yAxis <= 425)
            {
                if (!hoverSoundFxMute && !hoverContinue && !hoverStart)
                {
                    soundButtonHover.play();
                    hoverSoundFxMute = true;
                    hoverContinue = true;
                    hoverStart = true;
                }
                if(soundFxMute)
                {
                    state2 = textOff;
                    state2.setFillColor(Color::Green);
                }
                else
                {
                    state2 = textOn;
                    state2.setFillColor(Color::Red);
                }
                if (Mouse::isButtonPressed(Mouse::Left) && !pressedSoundFxMute)
                {
                    if(soundFxMute)
                        soundFxMute = false;
                    else
                        soundFxMute = true;

                    pressedSoundFxMute = true;
                }
            }
            else {
                hoverStart = false;
                hoverContinue = false;
                hoverSoundFxMute = false;
                state2.setFillColor(Color::White);
            }

            // Back arrow
            if (mouse_xAxis >= 44 && mouse_xAxis <= 163 && mouse_yAxis >= 51 && mouse_yAxis <= 104)
            {
                if (!hoverArrow)
                {
                    soundButtonHover.play();
                    hoverArrow = true;
                }
                arrow.setTexture(&textureRedArrow);
                if (Mouse::isButtonPressed(Mouse::Left))
                    settingsMenu = false;
            }
            else {
                hoverSoundFxMute = false;
                arrow.setTexture(&textureWhiteArrow);
            }
            state1.setPosition(740, 300);
            state2.setPosition(785, 400);
            window.draw(textSoundFx);
            window.draw(textMusic);
            window.draw(state1);
            window.draw(state2);
            window.draw(arrow);
        }

        // Render intro
        if (!started)
        {
            bool currentlyHovering = false;

            // Continue button
            if (mouse_xAxis >= 235 && mouse_xAxis <= 1045 && mouse_yAxis >= 405.5 && mouse_yAxis <= 454.5)
            {
                if (!hoverContinueIntro)
                {
                    soundButtonHover.play();
                    hoverContinueIntro = true;
                }
                currentlyHovering = true;
                if (Mouse::isButtonPressed(Mouse::Left))
                    started = true;
            }
            else {
                hoverContinueIntro = false;
                textContinueIntro.setFillColor(Color::White);
            }

            if (currentlyHovering)
            {
                Color colorContinue(0, 255, 0, continueFillColor -= ((continueFillColorInc) ? -5 : 5));
                textContinueIntro.setFillColor(colorContinue);
            }
            else
            {
                Color colorContinue(255, 255, 255, continueFillColor -= ((continueFillColorInc) ? -5 : 5));
                textContinueIntro.setFillColor(colorContinue);
            }

            window.draw(textIntro);
            window.draw(textContinueIntro);
        }
        window.display();
    }

    return 0;
}



