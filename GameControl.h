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
using namespace std;
using namespace sf;
using namespace sftools;

// Flags
bool guest = false;
bool canType = true;
bool paused = false;
bool started = false;
bool canClick = true;
bool musicMute = false;
bool hoverExit = false;
bool hoverStart = false;
bool hoverGuest = false;
bool hoverArrow = false;
bool hoverRetry = false;
bool hoverLevel1 = false;
bool hoverLevel2 = false;
bool bothPlayers = false;
bool soundFxMute = false;
bool gameStarted = false;
bool leaderboards = false;
bool settingsMenu = false;
bool levelInquire = false;
bool player1Input = false;
bool player2Input = false;
bool pushedFireBoy = false;
bool hoverContinue = false;
bool hoverSettings = false;
bool hoverMainMenu = false;
bool hoverMusicMute = false;
bool pushedWaterGirl = false;
bool pressedMusicMute = false;
bool hoverSoundFxMute = false;
bool hoverLeaderboards = false;
bool pressedSoundFxMute = false;
bool hoverContinueIntro = false;
bool continueFillColorInc = false;
bool hoverArrowLevelInquire = false;
bool hoverArrowLeaderboards = false;
bool enterYourNameFillColorInc = false;
bool hoverArrowLevelLeaderboard = false;
bool hoverTextLevels[10] = {};
bool levelLeaderboardPage[10] = {};

// Booleans for Gates
bool gateOpened[13];

// Booleans for bridges
bool bridgeOpened[13];

// Booleans for gate and bridge buttons
bool buttonGatePressed[13], buttonBridgePressed[13];

//Booleans for button sounds
bool gateButtonSoundPlayed[13];
bool bridgeButtonSoundPlayed[13];

RenderWindow window(VideoMode(1280, 720), "Fireboy and Watergirl", Style::Titlebar | Style::Close);
void initWindow()
{
    window.setFramerateLimit(60);
}
void initButtonSound()
{
    memset(bridgeButtonSoundPlayed, false, 13);
    memset(gateButtonSoundPlayed, false, 13);
}
Event event;
void gamePolling()
{
    while (window.pollEvent(event))
    {
        if (event.type == Event::Closed) {
            window.close();
        }
        if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape && gameStarted) {
            if (settingsMenu)
                settingsMenu = false;
            else if (paused)
                paused = false, chron.resume();
            else
                paused = true, chron.pause();
        }
        if (event.type == Event::KeyReleased && event.key.code == Keyboard::Return) {
            if (!started)
            {
                started = true;
                player1Input = true;
                textContinueIntro.setFillColor(Color::White);
            }
            else if (!gameStarted && !levelInquire && !player1Input && !player2Input)
            {
                chron.reset();
                chron.resume();
                gameStarted = true;
                musicIntro.stop();
                if (musicLevel.getStatus() != Music::Status::Playing)
                {
                    musicLevel.play();
                }
            }
        }
        if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left && canClick)
        {
            canClick = false;
            pressedMusicMute = false;
            pressedSoundFxMute = false;
        }

    }
}

bool FBDead = 0, WGDead = 0;

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
    if (!guest)
    {
        updateData(player1Name, player2Name, level, secondst + minutes * 60);
        initializeCurrentRecords();
        //getTopTenOfLevel(level);
    }
    else
    {
        guestRecords[level] = secondst + minutes * 60;
    }
}
