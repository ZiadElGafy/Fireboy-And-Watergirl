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
#include "Players.h"
#include "LevelGeneration.h"
using namespace std;
using namespace sf;
using namespace sftools;

// Players Positions for each level
vector< pair< pair<int,int>,pair<int,int> > > initialPosition =
{   // Level 1
    {{41.f,599.f},{41.f,599.f}},
    // Level 2
    {{41.f,599.f},{41.f,599.f}},
    // Level 3
    {{41.f,599.f},{41.f,599.f}},
    // Level 4
    {{41.f,599.f},{41.f,599.f}},
    // Level 5
    {{200.f,599.f},{200.f,599.f}},
    // Level 6
    {{1150.f,120.f},{250.f,120.f}}
};

// Flags

// Hover flags
bool hoverExit = false;
bool hoverSand = false;
bool hoverStart = false;
bool hoverStone = false;
bool hoverGuest = false;
bool hoverArrow = false;
bool hoverRetry = false;
bool hoverTheme = false;
bool hoverLevel1 = false;
bool hoverLevel2 = false;
bool hoverContinue = false;
bool hoverSettings = false;
bool hoverMainMenu = false;
bool hoverMusicMute = false;
bool hoverTextLevels[10] = {};
bool hoverSoundFxMute = false;
bool hoverArrowThemes = false;
bool hoverLeaderboards = false;
bool hoverContinueIntro = false;
bool hoverArrowLevelInquire = false;
bool hoverArrowLeaderboards = false;
bool hoverArrowLevelLeaderboard = false;

// Pages
bool guest = false;
bool paused = false;
bool started = false;
bool mainMenu = false;
bool themeMenu = false;
bool gameStarted = false;
bool levelInquire = false;
bool leaderboards = false;
bool settingsMenu = false;
bool levelLeaderboardPage[10] = {};

// Music
bool musicMute = false;
bool soundFxMute = false;
bool pressedMusicMute = false;
bool gateButtonSoundPlayed[13];
bool pressedSoundFxMute = false;
bool bridgeButtonSoundPlayed[13];

// Input
bool bothPlayers = false;
bool player1Input = false;
bool player2Input = false;

// Coloring
bool continueFillColorInc = false;
bool enterYourNameFillColorInc = false;

// Event handling
bool canType = true;
bool canClick = true;

// Platform collision
bool pushedFireBoy = false;
bool pushedWaterGirl = false;

// Gates
bool gateOpened[13];
bool buttonGatePressed[13];

// Gems
bool gemsTaken[11];

// Bridges
bool bridgeOpened[13];
bool buttonBridgePressed[13];

// Booleans for boxes
bool boxGroundCheck[13];
bool boxWatergirlPushed[13], boxFireboyPushed[13];

// Characters
bool FBDead = 0;
bool WGDead = 0;
bool oneDead = false;

// Mouse coordinate
float mouse_xAxis, mouse_yAxis;

// Safe zone
float safe = 5.f;

// Enemy
bool enemyMoveRight[10] = {};

// Window
RenderWindow window(VideoMode(1280, 720), "Fireboy and Watergirl", Style::Titlebar | Style::Close);

void initWindow()
{
    window.setFramerateLimit(60);
}

// Event
Event event;

void checkTheme()
{
    if(sand)
    {
        // Platform
        spriteStoneLeft.setTexture(&textureSandLeft);
        spriteStoneRight.setTexture(&textureSandRight);
        spriteStoneMid.setTexture(&textureSandMid);

        // BackGround
        spriteBackground.setTexture(&textureBackgroundSand);

        // Borders
        borders[2].setTexture(&textureSideBorderSand), borders[3].setTexture(&textureSideBorderSand);
        borders[0].setTexture(&textureTopBorderSand), borders[1].setTexture(&textureBottomBorderSand);

        // Button blocks
        buttonOn.setTexture(&textureButtonOnSand);
        buttonOff.setTexture(&textureButtonOffSand);

        // pools
        spriteLavaLeft.setTexture(lavaLeftSandText);
        spriteLavaMid.setTexture(lavaMidSandText);
        spriteLavaRight.setTexture(lavaRightSandText);
        spriteSmallLava.setTexture(smallLavaSandText);

        spriteWaterLeft.setTexture(waterLeftSandText);
        spriteWaterMid.setTexture(waterMidSandText);
        spriteWaterRight.setTexture(waterRightSandText);
        spriteSmallWater.setTexture(smallWaterSandText);

        spriteAcidLeft.setTexture(acidLeftSandText);
        spriteAcidMid.setTexture(acidMidSandText);
        spriteAcidRight.setTexture(acidRightSandText);
        spriteSmallAcid.setTexture(smallAcidSandText);

    }
    else if(stone)
    {
        // Platform
        spriteStoneLeft.setTexture(&textureStoneLeft);
        spriteStoneRight.setTexture(&textureStoneRight);
        spriteStoneMid.setTexture(&textureStoneMid);

        // BackGround
        spriteBackground.setTexture(&textureBackground);

        // Borders
        borders[2].setTexture(&textureSideBorder), borders[3].setTexture(&textureSideBorder);
        borders[0].setTexture(&textureTopBorder), borders[1].setTexture(&textureBottomBorder);

        // Button blocks
        buttonOn.setTexture(&textureButtonOn);
        buttonOff.setTexture(&textureButtonOff);

        // pools
        spriteLavaLeft.setTexture(lavaLeftText);
        spriteLavaMid.setTexture(lavaMidText);
        spriteLavaRight.setTexture(lavaRightText);
        spriteSmallLava.setTexture(smallLavaText);

        spriteWaterLeft.setTexture(waterLeftText);
        spriteWaterMid.setTexture(waterMidText);
        spriteWaterRight.setTexture(waterRightText);
        spriteSmallWater.setTexture(smallWaterText);

        spriteAcidLeft.setTexture(acidLeftText);
        spriteAcidMid.setTexture(acidMidText);
        spriteAcidRight.setTexture(acidRightText);
        spriteSmallAcid.setTexture(smallAcidText);
    }
}

void gamePolling()
{
    while (window.pollEvent(event))
    {
        // Close window
        if (event.type == Event::Closed) {
            window.close();
        }

        if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape && gameStarted) {
            // Resume
            if (paused && !FBDead && !WGDead && !settingsMenu)
                paused = false, chron.resume();
            // Pause
            else if (!FBDead && !WGDead)
                paused = true, chron.pause();
        }
    }
}

void leaderboardAndTextFlickering()
{
    // Check if on level leaderboard page
    for (int i = 0; i < 10; i++)
    {
        if (levelLeaderboardPage[i])
        {
            currentLevelLeaderboardPage = i + 1;
            leaderboards = false;
            break;
        }
    }

    // Check continue fill color increasing
    if (!continueFillColor) continueFillColorInc = true;
    else if (continueFillColor == 255) continueFillColorInc = false;

    // Check enter names fill color increasing
    if (!enterYourNameFillColor) enterYourNameFillColorInc = true;
    else if (enterYourNameFillColor == 255) enterYourNameFillColorInc = false;
}

void checkMusic()
{
    // Check level music
    if (soundLevelComplete.getStatus() != Music::Status::Playing && musicIntro.getStatus() != Music::Status::Playing && !gameStarted && !musicMute)
        musicIntro.play();
}

Time gameTime;
int secondst, minutes;

void gameTimer()
{
    // Getting elapsed time
    gameTime = chron.getElapsedTime();
    secondst = gameTime.asSeconds(); minutes = secondst / 60;
    secondst %= 60;

    // Adding the elapsed time into a string
    if (minutes <= 9)
        ss << 0;
    ss << minutes << ":";
    if (secondst <= 9)
        ss << 0;
    ss << secondst;
    ss >> stringTimer;
    ss.clear();
    textTimer.setString(stringTimer);
}

void getEndingTime()
{
    int gemsCollected = 0;
    for (auto i : gemsTaken)
    {
        gemsCollected += i;
    }
    if (!guest)
    {
        updateData(player1Name, player2Name, level, (secondst + minutes * 60));
        initializeCurrentRecords();
    }
    else
    {
        guestRecords[level] = secondst + minutes * 60;
    }
}

void initButtonSound()
{
    memset(bridgeButtonSoundPlayed, false, 13);
    memset(gateButtonSoundPlayed, false, 13);
}
void restartGems()
{
    memset(gemsTaken, false, sizeof gemsTaken);
}
void getMouseCoordinates()
{
    mouse_xAxis = Mouse::getPosition(window).x, mouse_yAxis = Mouse::getPosition(window).y;
}

void fillBool()
{
    mainMenu = !gameStarted && !paused && !settingsMenu && started && bothPlayers && !levelInquire && !leaderboards && !currentLevelLeaderboardPage && !themeMenu;
    oneDead = FBDead || WGDead;
}

void checkCurrentLevelOnScreen(Player& fireBoy, Player& waterGirl)
{
    if (level != curPlatformObjectLevel)
    {
        // Reset characters (Players)
        fireBoy.Restart(initialPosition[level].first.first,initialPosition[level].first.second);
        waterGirl.Restart(initialPosition[level].second.first,initialPosition[level].second.second);

        // Clearing all platforms from the old level
        platformObjects.clear();
        gatesObjects.clear();
        gemObjects.clear();
        boxes.clear();
        boxesPositions.clear();
        enemies.clear();

        // Pushing all platforms from the new level
        platformObjects.push_back({{ground,0},0});
        checkTheme();
        fillPlatformObjects();
        fillGateObjects();
        fillGemObjects();

        // Reset boolean arrays
        memset(gateOpened, 0, sizeof(gateOpened));
        memset(buttonGatePressed, 0, sizeof(bridgeOpened));
        memset(buttonGatePressed, 0, sizeof(buttonGatePressed));

        // Assign new level to current level
        curPlatformObjectLevel = level;

        deathX = deathY = -100.f;
    }
}

// Load idle texture into fireboy
void initFireBoyIdle(Player& fireBoy)
{
    fireBoy.playerSprite.setTexture(fireBoyTexture);
}

// Load idle texture into watergirl
void initWaterGirlIdle(Player& waterGirl)
{
    waterGirl.playerSprite.setTexture(waterGirlTexture);
}

// Letting characters fall due to gravity
void fall(Player& player, float gravity)
{
    player.move({0, gravity});
    
}

// Letting boxes fall due to gravity
void boxesFall(float gravity)
{
    for(int i = 0;i < boxes.size();++i)
    {
        boxes[i].move({0,gravity});
        for(auto j : platformObjects)
        {
            if (j.first.first.getPosition().y - boxes[i].getPosition().y <= 55 && j.first.first.getPosition().y - boxes[i].getPosition().y >= 0 )
            {
                if(boxes[i].getGlobalBounds().intersects(j.first.first.getGlobalBounds()))
                {
                 boxes[i].move({0, -gravity});
                }
            }
            
        }
        for(auto j : gatesObjects)
        {
            if (j.first.first.getPosition().y - boxes[i].getPosition().y <= 55 && j.first.first.getPosition().y - boxes[i].getPosition().y >= 0 && (j.first.second == 3 || j.first.second == 4) && bridgeOpened[j.second])
            {
                if(boxes[i].getGlobalBounds().intersects(j.first.first.getGlobalBounds()))
                {
                    boxes[i].move({0, -gravity});
                }
            }
        }
    }
   
}
    
// jump mechanics
void jumpMechanics(Player& player, float gravity)
{
    if (player.jumpCnt <= jumpFactor)
    {
        player.move({ 0, ((player.jumpCnt - (jumpFactor / 2)) / 2) });
        player.move({ 0, -gravity });
    }
}

// Fireboy jumping
void fireBoyJumping(Player& fireBoy, float iterationsPerSecond)
{
    if (Keyboard::isKeyPressed(Keyboard::Key::Up) && !paused && gameStarted)
    {
        // Check if fireboy is ready to jump
        if (!pushedFireBoy && fireBoy.jumpCnt > jumpFactor && fireBoy.ready >= iterationsPerSecond / 2 && fireBoy.groundCheck)
        {
            fireBoy.jumpCnt = 0;
            fireBoy.ready = 0;
            fireBoy.groundCheck = 0;
            if (!soundFxMute)
                soundFireboyJump.play();
        }
    }
}

// Watergirl jumping
void waterGirlJumping(Player& waterGirl, float iterationsPerSecond)
{
    if (Keyboard::isKeyPressed(Keyboard::Key::W) && !paused && gameStarted)
    {
        // Check if watergirl is ready to jump
        if (!pushedWaterGirl && waterGirl.jumpCnt > jumpFactor && waterGirl.ready >= iterationsPerSecond / 2 && waterGirl.groundCheck)
        {
            waterGirl.jumpCnt = 0;
            waterGirl.ready = 0;
            waterGirl.groundCheck = 0;
            if (!soundFxMute)
                soundWatergirlJump.play();
        }
    }
}

// Fireboy moving left
void fireBoyMovingLeft(Player& fireBoy, float pixelsPerIteration)
{
    if (Keyboard::isKeyPressed(Keyboard::Key::Left) && !paused && gameStarted)
    {
        // Applying left facing fireboy texture to fireboy
        fireBoy.playerSprite.setTexture(fireBoyTextureLeft);

        if (!pushedFireBoy && fireBoy.jumpCnt >= jumpFactor) fireBoy.move({-pixelsPerIteration , 0});
        else if (!pushedFireBoy) fireBoy.move({-1.825 * pixelsPerIteration , 0});
    }
}

// Fireboy moving right
void fireBoyMovingRight(Player& fireBoy, float pixelsPerIteration)
{
    if (Keyboard::isKeyPressed(Keyboard::Key::Right) && !paused && gameStarted)
    {
        // Applying right facing fireboy texture to fireboy
        fireBoy.playerSprite.setTexture(fireBoyTextureRight);

        if (!pushedFireBoy && fireBoy.jumpCnt >= jumpFactor) fireBoy.move({pixelsPerIteration , 0});
        else if (!pushedFireBoy)fireBoy.move({1.825 * pixelsPerIteration , 0});
    }
}

// Watergirl moving left
void waterGirlMovingLeft(Player& waterGirl, float pixelsPerIteration)
{
    if (Keyboard::isKeyPressed(Keyboard::Key::A) && !paused && gameStarted)
    {
        // Applying left facing watergirl texture to watergirl
        waterGirl.playerSprite.setTexture(waterGirlTextureLeft);

        if (!pushedWaterGirl && waterGirl.jumpCnt >= jumpFactor) waterGirl.move({-pixelsPerIteration , 0});
        else if (!pushedWaterGirl) waterGirl.move({-1.825 * pixelsPerIteration , 0});
    }
}

// Watergirl moving right
void waterGirlMovingRight(Player& waterGirl, float pixelsPerIteration)
{
    if (Keyboard::isKeyPressed(Keyboard::Key::D) && !paused && gameStarted)
    {
        // Applying right facing watergirl texture to watergirl
        waterGirl.playerSprite.setTexture(waterGirlTextureRight);

        if (!pushedWaterGirl && waterGirl.jumpCnt >= jumpFactor) waterGirl.move({pixelsPerIteration , 0});
        else if (!pushedWaterGirl) waterGirl.move({1.825 * pixelsPerIteration , 0});
    }
}

// Jump cnt increments
void incrementJumpCnts(Player& fireBoy, Player& waterGirl)
{
    if (fireBoy.jumpCnt < 100)
    {
        fireBoy.jumpCnt++;
    }
    if (waterGirl.jumpCnt < 100)
    {
        waterGirl.jumpCnt++;
    }
}

// Watergirl Y-axis platform collision
void waterGirlPlatformCollision(Player& waterGirl, pair<pair<RectangleShape, int>, int> i, float gravity)
{
    if (waterGirl.bounds.intersects(i.first.first.getGlobalBounds()))
    {
        waterGirl.jumpCnt = jumpFactor + 1;
        if (waterGirl.dy < i.first.first.getPosition().y)
        {
            pushedWaterGirl = false;
            waterGirl.move({0, -gravity});
            waterGirl.groundCheck = 1;

            // Watergirl death (Players)
            if ((i.first.second == 1 || i.first.second == 3) && !waterGirl.isDead)
            {
                waterGirl.die();
                if (!soundFxMute) soundPlayerDeath.play();
                deathX = i.first.first.getPosition().x; deathY = i.first.first.getPosition().y - 40;
                smoke1.setPosition({deathX, deathY});
                smoke2.setPosition({deathX, deathY});
            }

            // Gate opening (Game control)
            if (i.first.second == 4)
            {
                buttonGatePressed[i.second] = true;
            }

            // Bridge opening (Game control)
            if (i.first.second == 5)
            {
                buttonBridgePressed[i.second] = true;
            }
        }
    }
}

// Fireboy Y-axis platform collision
void fireBoyPlatformCollision(Player& fireBoy, pair<pair<RectangleShape, int>, int> i, float gravity)
{
    if (fireBoy.bounds.intersects(i.first.first.getGlobalBounds()))
    {
        fireBoy.jumpCnt = jumpFactor + 1;
        if (fireBoy.dy < i.first.first.getPosition().y)
        {
            pushedFireBoy = false;
            fireBoy.move({0, -gravity});
            fireBoy.groundCheck = 1;

            // Fireboy death (Players)
            if ((i.first.second == 2 || i.first.second == 3) && !fireBoy.isDead)
            {
                fireBoy.die();
                if (!soundFxMute)soundPlayerDeath.play();
                deathX = i.first.first.getPosition().x; deathY = i.first.first.getPosition().y - 40;
                smoke1.setPosition({deathX, deathY});
                smoke2.setPosition({deathX, deathY});
            }
            // Gate opening (Game control)
            if (i.first.second == 4)
            {
                buttonGatePressed[i.second] = true;
            }

            // Bridge opening (Game control)
            if (i.first.second == 5)
            {
                buttonBridgePressed[i.second] = true;
            }

        }
    }
}

// Watergirl pushed right
void waterGirlPushedRight(Player& waterGirl, pair<pair<RectangleShape, int>, int> i, float pixelsPerIteration)
{
    if (waterGirl.bounds.intersects(i.first.first.getGlobalBounds()) && waterGirl.dy + 80 - safe >= i.first.first.getPosition().y && waterGirl.dx + 80 - safe >= i.first.first.getPosition().x)
    {
        pushedWaterGirl = true;
        waterGirl.move({pixelsPerIteration, 0});
    }
}

// Watergirl pushed left
void waterGirlPushedLeft(Player& waterGirl, pair<pair<RectangleShape, int>, int> i, float pixelsPerIteration)
{
    if (waterGirl.bounds.intersects(i.first.first.getGlobalBounds()) && waterGirl.dy + 80 - safe >= i.first.first.getPosition().y && waterGirl.dx + safe <= i.first.first.getPosition().x + i.first.first.getGlobalBounds().width)
    {
        pushedWaterGirl = true;
        waterGirl.move({-pixelsPerIteration, 0});
    }

}

// Fireboy pushed right
void fireBoyPushedRight(Player& fireBoy, pair<pair<RectangleShape, int>, int> i, float pixelsPerIteration)
{
    if (fireBoy.bounds.intersects(i.first.first.getGlobalBounds()) && fireBoy.dy + 80 - safe >= i.first.first.getPosition().y && fireBoy.dx + 80 - safe >= i.first.first.getPosition().x)
    {
        pushedFireBoy = true;
        fireBoy.move({pixelsPerIteration, 0});
    }

}

// Fireboy pushed left
void fireBoyPushedLeft(Player& fireBoy, pair<pair<RectangleShape, int>, int> i, float pixelsPerIteration)
{
    if (fireBoy.bounds.intersects(i.first.first.getGlobalBounds()) && fireBoy.dy + 80 - safe >= i.first.first.getPosition().y && fireBoy.dx + safe <= i.first.first.getPosition().x + i.first.first.getGlobalBounds().width)
    {
        pushedFireBoy = true;
        fireBoy.move({-pixelsPerIteration, 0});
    }
}

// Watergirl Y-axis bridge collision
void waterGirlBridgeCollision(Player& waterGirl, pair<pair<RectangleShape, int>, int> i, float gravity)
{
    if ((i.first.second == 3 || i.first.second == 4) && waterGirl.bounds.intersects(i.first.first.getGlobalBounds()))
    {
        if (abs(waterGirl.dy - i.first.first.getPosition().y) < 70 && bridgeOpened[i.second])
        {
            waterGirl.jumpCnt = jumpFactor + 1;
        }
        if (waterGirl.dy < i.first.first.getPosition().y && bridgeOpened[i.second])
        {
            pushedWaterGirl = false;
            waterGirl.move({0, -gravity});
            waterGirl.groundCheck = 1;
        }
    }
}

// Fireboy Y-axis bridge collision
void fireBoyBridgeCollision(Player& fireBoy, pair<pair<RectangleShape, int>, int> i, float gravity)
{
    if ((i.first.second == 3 || i.first.second == 4) && fireBoy.bounds.intersects(i.first.first.getGlobalBounds()))
    {
        if (abs(fireBoy.dy - i.first.first.getPosition().y) < 70 && bridgeOpened[i.second])
        {
            fireBoy.jumpCnt = jumpFactor + 1;
        }
        if (fireBoy.dy < i.first.first.getPosition().y && bridgeOpened[i.second])
        {
            pushedFireBoy = false;
            fireBoy.move({0, -gravity});
            fireBoy.groundCheck = 1;
        }
    }
}

// Watergirl pushed right bridge
void waterGirlPushedRightBridge(Player& waterGirl, pair<pair<RectangleShape, int>, int> i, float pixelsPerIteration)
{
    if (waterGirl.bounds.intersects(i.first.first.getGlobalBounds()) && waterGirl.dy + 80 - safe >= i.first.first.getPosition().y && waterGirl.dx + 20 - safe >= i.first.first.getPosition().x && !gateOpened[i.second] && i.first.second != 3 && i.first.second != 4)
    {
        pushedWaterGirl = true;
        waterGirl.move({pixelsPerIteration, 0});
    }
}

// Watergirl pushed left bridge
void waterGirlPushedLeftBridge(Player& waterGirl, pair<pair<RectangleShape, int>, int> i, float pixelsPerIteration)
{
    if (waterGirl.bounds.intersects(i.first.first.getGlobalBounds()) && waterGirl.dy + 80 - safe >= i.first.first.getPosition().y && waterGirl.dx + safe <= i.first.first.getPosition().x + i.first.first.getGlobalBounds().width && !gateOpened[i.second] && i.first.second != 3 && i.first.second != 4)
    {
        pushedWaterGirl = true;
        waterGirl.move({-pixelsPerIteration, 0});
    }
}

// Fireboy pushed right bridge
void fireBoyPushedRightBridge(Player& fireBoy, pair<pair<RectangleShape, int>, int> i, float pixelsPerIteration)
{
    if (fireBoy.bounds.intersects(i.first.first.getGlobalBounds()) && fireBoy.dy + 80 - safe >= i.first.first.getPosition().y && fireBoy.dx + 20 - safe >= i.first.first.getPosition().x && !gateOpened[i.second] && i.first.second != 3 && i.first.second != 4)
    {
        pushedFireBoy = true;
        fireBoy.move({pixelsPerIteration, 0});
    }
}

// Fireboy pushed left bridge
void fireBoyPushedLeftBridge(Player& fireBoy, pair<pair<RectangleShape, int>, int> i, float pixelsPerIteration)
{
    if (fireBoy.bounds.intersects(i.first.first.getGlobalBounds()) && fireBoy.dy + 80 - safe >= i.first.first.getPosition().y && fireBoy.dx + safe <= i.first.first.getPosition().x + i.first.first.getGlobalBounds().width && !gateOpened[i.second] && i.first.second != 3 && i.first.second != 4)
    {
        pushedFireBoy = true;
        fireBoy.move({-pixelsPerIteration, 0});
    }
}

// gem collision
void gemCollision(Player& player, pair<pair<RectangleShape, int>, int> i)
{
    if (player.bounds.intersects(i.first.first.getGlobalBounds()))
    {
        if (!gemsTaken[i.second] && !soundFxMute)
        {
            Time fadeTime;
            fadeTime = seconds(-2);
            chron.add(fadeTime);
            soundGem.play();
        }
        gemsTaken[i.second] = true;
    }
}

// Restart enemies
void restartEnemies() {
    for (int i = 0; i < enemies.size(); i++) {
        enemies[i].first.setPosition({ enemies[i].second.first,enemies[i].second.second });
        enemies[i].first.setTexture(&enemyRightText);
    }
}

// Enemy motion and collision with characters
void enemyMotionAndCollision(Player& fireBoy, Player& waterGirl)
{
    // Enemy motion FireBoy
    for (int i = 0; i < enemies.size(); i++) {
        float startPos = enemies[i].second.first;
        float endPos = startPos + 320;
        if(paused)
            continue;
        if (fireBoy.dx >= enemies[i].second.first && fireBoy.dx <= enemies[i].second.first + 320 && fireBoy.dy < enemies[i].second.second && fireBoy.dy+170 > enemies[i].second.second) {
            if (fireBoy.dx < enemies[i].first.getPosition().x) {
                enemies[i].first.setTexture(&enemyLeftText);
                enemies[i].first.move({ -0.8,0 });
            }
            else {
                enemies[i].first.setTexture(&enemyRightText);
                enemies[i].first.move({ 0.8,0 });
            }
        }
            // Enemy motion WaterGirl
        else if (waterGirl.dx >= enemies[i].second.first && waterGirl.dx <= enemies[i].second.first + 320 && waterGirl.dy < enemies[i].second.second && waterGirl.dy + 170 > enemies[i].second.second) {
            if (waterGirl.dx < enemies[i].first.getPosition().x) {
                enemies[i].first.setTexture(&enemyLeftText);
                enemies[i].first.move({ -0.8,0 });
            }
            else {
                enemies[i].first.setTexture(&enemyRightText);
                enemies[i].first.move({ 0.8,0 });
            }
        }
        else {
            if (!enemyMoveRight[i] && !paused) {
                enemies[i].first.setTexture(&enemyLeftText);
                enemies[i].first.move({ -0.8,0 });
            }
            else if (enemyMoveRight[i] && !paused) {
                enemies[i].first.setTexture(&enemyRightText);
                enemies[i].first.move({ 0.8,0 });
            }

        }
        if (enemies[i].first.getPosition().x <= startPos) {
            enemyMoveRight[i] = 1;
        }
        if (enemies[i].first.getPosition().x >= endPos) {
            enemyMoveRight[i] = 0;
        }
        if (fireBoy.bounds.intersects(enemies[i].first.getGlobalBounds())) {
            fireBoy.die();
            if (!soundFxMute)
                soundPlayerDeath.play();
        }

        if (waterGirl.bounds.intersects(enemies[i].first.getGlobalBounds())) {
            waterGirl.die();
            if (!soundFxMute)
                soundPlayerDeath.play();
        }
    }
}
// Boxes motion and collision
void boxesMotionAndCollision(Player& fireBoy, Player& waterGirl, float pixelsPerIteration, float gravity)
{
    bool gateBoxCollision[13] = { false };
    bool BridgeBoxCollision[13] = { false };
    bool platformBoxCollision[13] = {};
    for (int i = 0; i < boxes.size(); ++i)
    {

        // Box and Gate Collision
        for(auto j:gatesObjects)
        {
            if(boxes[i].getGlobalBounds().intersects(j.first.first.getGlobalBounds()) && !gateOpened[j.second] && j.first.second <= 2)
            {
                gateBoxCollision[i] = true;
            }
        }
        // X-axis with platform objects
        for(auto j:platformObjects)
        {
            if(boxes[i].getGlobalBounds().intersects(j.first.first.getGlobalBounds()) && j.first.second == 0)
            {
                platformBoxCollision[i] = true;
            }
            if(boxes[i].getPosition().x <= 41.f || boxes[i].getPosition().x >= 1180.f)
            {
                platformBoxCollision[i] = true;
            }
        }
        // X-axis with players
        fireBoy.Inquire();
        waterGirl.Inquire();
        if ((waterGirl.bounds.intersects(boxes[i].getGlobalBounds()) && waterGirl.dy + 60 - safe >= boxes[i].getPosition().y && waterGirl.dx + 75 <= boxes[i].getPosition().x))
        {

            pushedWaterGirl = true;
            boxWatergirlPushed[i] = true;
            if(!boxFireboyPushed[i] && !gateBoxCollision[i] && !platformBoxCollision[i])
            {

                waterGirl.move({- pixelsPerIteration/20, 0 });
                boxes[i].move({ pixelsPerIteration, 0 });
            }
            else
            {
                waterGirl.move({- pixelsPerIteration, 0 });
            }
        }
        else if ((waterGirl.bounds.intersects(boxes[i].getGlobalBounds()) && waterGirl.dy + 60 - safe >= boxes[i].getPosition().y && waterGirl.dx + safe >= boxes[i].getPosition().x + boxes[i].getGlobalBounds().width))
        {

            pushedWaterGirl = true;
            boxWatergirlPushed[i] = true;
            if(!boxFireboyPushed[i] && !gateBoxCollision[i] && !platformBoxCollision[i])
            {
                waterGirl.move({ pixelsPerIteration/20, 0 });
                boxes[i].move({ -pixelsPerIteration, 0 });
            }
            else
            {
                waterGirl.move({ pixelsPerIteration, 0 });
            }

        }
        else
        {
            boxWatergirlPushed[i] = false;
        }
        if ((fireBoy.bounds.intersects(boxes[i].getGlobalBounds()) && fireBoy.dy + 60 - safe >= boxes[i].getPosition().y && fireBoy.dx + 75 <= boxes[i].getPosition().x) )
        {

            pushedFireBoy = true;
            boxFireboyPushed[i] = true;
            if(!boxWatergirlPushed[i] && !gateBoxCollision[i] && !platformBoxCollision[i])
            {
                fireBoy.move({- pixelsPerIteration/20, 0 });
                boxes[i].move({ pixelsPerIteration, 0 });
            }
            else{
                fireBoy.move({- pixelsPerIteration, 0 });
            }
        }
        else if ((fireBoy.bounds.intersects(boxes[i].getGlobalBounds()) && fireBoy.dy + 60 - safe >= boxes[i].getPosition().y && fireBoy.dx + safe >= boxes[i].getPosition().x + boxes[i].getGlobalBounds().width))
        {

            pushedFireBoy = true;
            boxFireboyPushed[i] = true;
            if(!boxWatergirlPushed[i] && !gateBoxCollision[i] && !platformBoxCollision[i])
            {
                fireBoy.move({ pixelsPerIteration/20, 0 });
                boxes[i].move({ -pixelsPerIteration, 0 });
            }
            else
            {
                fireBoy.move({ pixelsPerIteration, 0 });
            }
        }
        else
        {
            boxFireboyPushed[i] = false;
        }
        //Y-axis waterGirl and fireBoy collision on box

        if ( waterGirl.bounds.intersects(boxes[i].getGlobalBounds()))
        {
            if (waterGirl.dy < boxes[i].getPosition().y )
            {
                pushedFireBoy = false;
                waterGirl.move({ 0, -gravity });
                waterGirl.groundCheck = 1;
            }
        }
        if ( fireBoy.bounds.intersects(boxes[i].getGlobalBounds()))
        {
            if (fireBoy.dy < boxes[i].getPosition().y )
            {
                pushedFireBoy = false;
                fireBoy.move({ 0, -gravity });
                fireBoy.groundCheck = 1;
            }
        }

    }
}