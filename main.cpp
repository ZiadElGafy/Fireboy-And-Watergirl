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
#include "DataRetrieval.h"
#include "Visuals.h"
#include "LevelGeneration.h"
#include "Players.h"
#include "GameControl.h"
#include "Render.h"
using namespace std;
using namespace sf;
using namespace sftools;

float gravity = 7;

int main()
{
    // Initializing all the visuals (Visuals)
    initVisuals();
    initVisuals();

    // Declaring characters
    Player fireBoy(fireBoyTexture, 1), waterGirl(waterGirlTexture, 2);

    // Initializing the window (Game control)
    initWindow();

    // Retrieving leaderboard from csv file (Data retrieval)
    initializeCurrentRecords();

    // Initializing button sound (Game control)
    initButtonSound();

    // Fill gem objects vector (Level generation)
    fillGemObjects();

    Clock clock;

    memset(enemyMoveRight, true, sizeof enemyMoveRight);

    // Main game loop
    while (window.isOpen())
    {
        // Check if on one of the level leaderboard pages (Game control)
        leaderboardAndTextFlickering();

        // Check theme
        checkTheme();

        // Jump cnt increments (Game control)
        incrementJumpCnts(fireBoy, waterGirl);

        // Speed and clock calculations
        Time timePerIteration;
        timePerIteration = clock.restart();

        float speed = 150;
        float iterationsPerSecond = 1.f / timePerIteration.asSeconds();
        float pixelsPerIteration = speed / iterationsPerSecond;

        // Checking if fireboy or watergirl are dead (Players)
        if (fireBoy.isDead || waterGirl.isDead)
        {
            deathCounter++;
        }

        // Reset death counter
        if (deathCounter >= (1.5 * iterationsPerSecond))
        {
            paused = 1;
            deathCounter = 0;
        }

        // Resistance for platforms
        for (auto i : platformObjects)
        {
            // Get X and Y positions for watergirl and check if it has collided with the border (Players)
            waterGirl.Inquire();

            // Y-axis (Game control)
            waterGirlPlatformCollision(waterGirl, i, gravity);

            // Get X and Y positions for fireboy and check if it has collided with the border (Players)
            fireBoy.Inquire();

            // Y-axis (Game control)
            fireBoyPlatformCollision(fireBoy, i, gravity);

            // X-axis

            // Get X and Y positions for watergirl and check if it has collided with the border (Players)
            waterGirl.Inquire();

            // Watergirl pushed right (Game control)
            waterGirlPushedRight(waterGirl, i, pixelsPerIteration);

            // Get X and Y positions for watergirl and check if it has collided with the border (Players)
            waterGirl.Inquire();

            // Watergirl pushed left (Game control)
            waterGirlPushedLeft(waterGirl, i, pixelsPerIteration);

            // Get X and Y positions for fireboy and check if it has collided with the border (Players)
            fireBoy.Inquire();

            // Fireboy pushed right (Game control)
            fireBoyPushedRight(fireBoy, i, pixelsPerIteration);

            // Get X and Y positions for fireboy and check if it has collided with the border (Players)
            fireBoy.Inquire();

            // Fireboy pushed left (Game control)
            fireBoyPushedLeft(fireBoy, i, pixelsPerIteration);
        }

        // Resistance for gates
        for (auto i : gatesObjects)
        {
            // Y-axis for bridges

            // Watergirl bridge collision (Game control)
            waterGirlBridgeCollision(waterGirl, i, gravity);

            // Fireboy bridge collision (Game control)
            fireBoyBridgeCollision(fireBoy, i, gravity);

            // X-axis for bridges

            // Get X and Y positions for watergirl and check if it has collided with the border (Players)
            waterGirl.Inquire();

            // Watergirl pushed right by bridge (Game control)
            waterGirlPushedRightBridge(waterGirl, i, pixelsPerIteration);

            // Get X and Y positions for watergirl and check if it has collided with the border (Players)
            waterGirl.Inquire();

            // Watergirl pushed left by bridge (Game control)
            waterGirlPushedLeftBridge(waterGirl, i, pixelsPerIteration);

            // Get X and Y positions for fireboy and check if it has collided with the border (Players)
            fireBoy.Inquire();

            // Fireboy pushed right by bridge (Game control)
            fireBoyPushedRightBridge(fireBoy, i, pixelsPerIteration);

            // Get X and Y positions for fireboy and check if it has collided with the border (Players)
            fireBoy.Inquire();

            // Fireboy pushed left by bridge (Game control)
            fireBoyPushedLeftBridge(fireBoy, i, pixelsPerIteration);
        }

        // Resistance for gems
        for (auto i : gemObjects)
        {
            // Get X and Y positions for fireboy and check if it has collided with the border (Players)
            fireBoy.Inquire();

            // Fireboy gems collision (Game control)
            if (i.first.second == 0)
                gemCollision(fireBoy, i);

            // Get X and Y positions for watergirl and check if it has collided with the border (Players)
            waterGirl.Inquire();

            // Watergirl gems collision (Game control)
            if (i.first.second == 1)
                gemCollision(waterGirl, i);
        }
        // Letting the boxes fall
        boxesFall(gravity);
        
        // Loading idle textures into fireboy (Game control)
        initFireBoyIdle(fireBoy);

        // Loading idle textures into watergirl (Game control)
        initWaterGirlIdle(waterGirl);

        // Letting the fireboy fall due to gravity (Game control)
        fall(fireBoy, gravity);

        // Letting the watergirl fall due to gravity (Game control)
        fall(waterGirl, gravity);
        
        // Watergirl moving right (Game control)
        waterGirlMovingRight(waterGirl, pixelsPerIteration);

        // Watergirl moving left (Game control)
        waterGirlMovingLeft(waterGirl, pixelsPerIteration);

        // Fireboy moving right (Game control)
        fireBoyMovingRight(fireBoy, pixelsPerIteration);

        // Fireboy moving left (Game control)
        fireBoyMovingLeft(fireBoy, pixelsPerIteration);

        // Watergirl jumping (Game control)
        waterGirlJumping(waterGirl, iterationsPerSecond);

        // Fireboy jumping (Game control)
        fireBoyJumping(fireBoy, iterationsPerSecond);

        // Fireboy jump mechanics (Game control)
        jumpMechanics(fireBoy, gravity);

        // Watergirl jump mechanics (Game control)
        jumpMechanics(waterGirl, gravity);

        waterGirl.ready++;
        fireBoy.ready++;

        // Enemy motion and collision with characters
        enemyMotionAndCollision(fireBoy, waterGirl);

        // Side Barriers (Players)
        waterGirl.Inquire();
        fireBoy.Inquire();

        // Check if music intro is supposed to play but it is not playing (Game control)
        checkMusic();

        // Updating timer on screen (Game control)
        gameTimer();

        // Event polling (Game control)
        gamePolling();

        // Clearing current objects on the screen
        window.clear();

        // Rendering background (Render)
        renderBackground();

        // Rendering all the objects in the current level being played
        if (gameStarted && !levelInquire && !leaderboards && !currentLevelLeaderboardPage)
        {
            // Check if on mute
            if (musicMute) musicLevel.stop();

            // Render door (Render)
            renderDoor();

            // Check if current level on the screen is not the one the player chose to play (Game control)
            checkCurrentLevelOnScreen(fireBoy, waterGirl);

            // Render gates (Render)
            renderGates();

            // Render gems (Render)
            renderGems();

            // Render level (Render)
            renderLevel();

            // Check if fireboy and Watergirl is still inside the drawn borders (Players)
            fireBoy.Inquire();
            waterGirl.Inquire();

            // Boxes motion and collision
            boxesMotionAndCollision(fireBoy, waterGirl, pixelsPerIteration, gravity);

            // Render boxes (Render)
            renderBoxes();

            // Render pools (Render)
            renderPools(fireBoy, waterGirl);

            // Render borders (Render)
            renderBorders();

            // Render characters (Render)
            renderCharacters(fireBoy, waterGirl);

            // Render enemies (Render)
            renderEnemies();

            // Render smoke (Render)
            renderSmoke();

            // Render timer (Render)
            renderTimer();

            // Render level ending (Render)
            renderLevelEnding(fireBoy, waterGirl);

            // Render pause background (Render)
            renderPauseBackground();
        }

        // Allow the player to enter keyboard events
        if (event.type == Event::KeyReleased)
            canType = true;

        // Allow the player to enter mouse events
        if (event.type == Event::MouseButtonReleased)
            canClick = true;

        // Mark the death of fireboy (Players)
        if (fireBoy.isDead)
            FBDead = 1;

        // Mark the death of watergirl (Players)
        if (waterGirl.isDead)
            WGDead = 1;

        // Render intro page (Render)
        renderIntro();

        // Render exit button (Render)
        renderExit();

        // Render enter your name and play as a guest page (Render)
        renderEnterYourName();

        // Render first player name (Render)
        renderFirstPlayerName();

        // Render second player name (Render)
        renderSecondPlayerName();

        // Render main menu page (Render)
        renderMainMenu();

        // render themes mune (Render)
        renderTheme();

        // Render settings button (Render)
        renderSettingsButton();

        // Render level inquire page (Render)
        renderLevelInquire();

        // Render leaderboards page (Render)
        renderLeaderboards();

        // Render current level leaderboard page (Render)
        renderCurrentLevelLeaderboard();

        // Render settings page (Render)
        renderSettings();

        // Render paused page (Render)
        renderPaused(fireBoy, waterGirl);

        // Display
        window.display();
    }
    return 0;
}
