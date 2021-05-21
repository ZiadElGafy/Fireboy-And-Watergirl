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
    initVisuals();
    initVisuals();

    Player fireBoy(fireBoyTexture, 1), waterGirl(waterGirlTexture, 2);

    initWindow();

    initializeCurrentRecords();

    initButtonSound();

    Clock clock;

    // Main game loop
    while (window.isOpen())
    {
        leaderboardAndTextFlickering();

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
        
        if (fireBoy.isDead || waterGirl.isDead) { deathCounter++; }
        if (deathCounter >= (1.5 * iterationsPerSecond)) { paused = 1; deathCounter = 0; }

        //Resistance for platforms
        for (auto i : platformObjects)
        {
            waterGirl.Inquire();
            //Y-axis
            if (waterGirl.bounds.intersects(i.first.first.getGlobalBounds()))
            {
                waterGirl.jumpCnt = jumpFactor + 1;
                if (waterGirl.dy < i.first.first.getPosition().y)
                {
                    pushedWaterGirl = false;
                    waterGirl.move({ 0, -gravity });
                    waterGirl.groundCheck = 1;
                    if ((i.first.second == 1 || i.first.second == 3) && !waterGirl.isDead)
                    {
                        waterGirl.die();
                        if (!soundFxMute)soundPlayerDeath.play();
                        deathX = i.first.first.getPosition().x; deathY = i.first.first.getPosition().y - 40;
                        smoke1.setPosition({ deathX, deathY });
                        smoke2.setPosition({ deathX, deathY });
                    }
                    if (i.first.second == 4)
                    {
                        buttonGatePressed[i.second] = true;
                    }
                    if (i.first.second == 5)
                    {
                        buttonBridgePressed[i.second] = true;
                    }

                }
            }
            fireBoy.Inquire();
            if (fireBoy.bounds.intersects(i.first.first.getGlobalBounds()))
            {
                fireBoy.jumpCnt = jumpFactor + 1;
                if (fireBoy.dy < i.first.first.getPosition().y)
                {
                    pushedFireBoy = false;
                    fireBoy.move({ 0, -gravity });
                    fireBoy.groundCheck = 1;
                    if ((i.first.second == 2 || i.first.second == 3) && !fireBoy.isDead) {
                        fireBoy.die();
                        if (!soundFxMute)soundPlayerDeath.play();
                        deathX = i.first.first.getPosition().x; deathY = i.first.first.getPosition().y - 40;
                        smoke1.setPosition({ deathX, deathY });
                        smoke2.setPosition({ deathX, deathY });
                    }
                    if (i.first.second == 4)
                    {
                        buttonGatePressed[i.second] = true;
                    }
                    if (i.first.second == 5)
                    {
                        buttonBridgePressed[i.second] = true;
                    }

                }
            }

            //X-axis
            waterGirl.Inquire();
            if (waterGirl.bounds.intersects(i.first.first.getGlobalBounds()) && waterGirl.dy + 80 - safe >= i.first.first.getPosition().y && waterGirl.dx + 80 - safe >= i.first.first.getPosition().x)
            {
                pushedWaterGirl = true;
                waterGirl.move({ pixelsPerIteration, 0 });
            }
            waterGirl.Inquire();
            if (waterGirl.bounds.intersects(i.first.first.getGlobalBounds()) && waterGirl.dy + 80 - safe >= i.first.first.getPosition().y && waterGirl.dx + safe <= i.first.first.getPosition().x + i.first.first.getGlobalBounds().width)
            {
                pushedWaterGirl = true;
                waterGirl.move({ -pixelsPerIteration, 0 });
            }
            fireBoy.Inquire();
            if (fireBoy.bounds.intersects(i.first.first.getGlobalBounds()) && fireBoy.dy + 80 - safe >= i.first.first.getPosition().y && fireBoy.dx + 80 - safe >= i.first.first.getPosition().x)
            {
                pushedFireBoy = true;
                fireBoy.move({ pixelsPerIteration, 0 });
            }
            if (fireBoy.bounds.intersects(i.first.first.getGlobalBounds()) && fireBoy.dy + 80 - safe >= i.first.first.getPosition().y && fireBoy.dx + safe <= i.first.first.getPosition().x + i.first.first.getGlobalBounds().width)
            {
                pushedFireBoy = true;
                fireBoy.move({ -pixelsPerIteration, 0 });
            }
        }

        //Resistance for gates
        for (auto i : gatesObjects)
        {
            // Y-axis for bridges
            if ((i.first.second == 3 || i.first.second == 4) && waterGirl.bounds.intersects(i.first.first.getGlobalBounds()))
            {
                waterGirl.jumpCnt = jumpFactor + 1;
                if (waterGirl.dy < i.first.first.getPosition().y && bridgeOpened[i.second])
                {
                    pushedWaterGirl = false;
                    waterGirl.move({ 0, -gravity });
                    waterGirl.groundCheck = 1;
                }
            }
            if ((i.first.second == 3 || i.first.second == 4) && fireBoy.bounds.intersects(i.first.first.getGlobalBounds()))
            {
                fireBoy.jumpCnt = jumpFactor + 1;
                if (fireBoy.dy < i.first.first.getPosition().y && bridgeOpened[i.second])
                {
                    pushedFireBoy = false;
                    fireBoy.move({ 0, -gravity });
                    fireBoy.groundCheck = 1;
                }
            }

            //X-axis
            if (waterGirl.bounds.intersects(i.first.first.getGlobalBounds()) && waterGirl.dy + 80 - safe >= i.first.first.getPosition().y && waterGirl.dx + 20 - safe >= i.first.first.getPosition().x && !gateOpened[i.second])
            {
                pushedWaterGirl = true;
                waterGirl.move({ pixelsPerIteration, 0 });
            }
            waterGirl.Inquire();
            if (waterGirl.bounds.intersects(i.first.first.getGlobalBounds()) && waterGirl.dy + 80 - safe >= i.first.first.getPosition().y && waterGirl.dx + safe <= i.first.first.getPosition().x + i.first.first.getGlobalBounds().width && !gateOpened[i.second])
            {
                pushedWaterGirl = true;
                waterGirl.move({ -pixelsPerIteration, 0 });
            }
            fireBoy.Inquire();
            if (fireBoy.bounds.intersects(i.first.first.getGlobalBounds()) && fireBoy.dy + 80 - safe >= i.first.first.getPosition().y && fireBoy.dx + 20 - safe >= i.first.first.getPosition().x && !gateOpened[i.second])
            {
                pushedFireBoy = true;
                fireBoy.move({ pixelsPerIteration, 0 });
            }
            if (fireBoy.bounds.intersects(i.first.first.getGlobalBounds()) && fireBoy.dy + 80 - safe >= i.first.first.getPosition().y && fireBoy.dx + safe <= i.first.first.getPosition().x + i.first.first.getGlobalBounds().width && !gateOpened[i.second])
            {
                pushedFireBoy = true;
                fireBoy.move({ -pixelsPerIteration, 0 });
            }

        }

        fireBoy.playerSprite.setTexture(fireBoyTexture);
        waterGirl.playerSprite.setTexture(waterGirlTexture);

        waterGirl.move({ 0, gravity });
        fireBoy.move({ 0, gravity });

        if (Keyboard::isKeyPressed(Keyboard::Key::D) && !paused && gameStarted)
        {
            waterGirl.playerSprite.setTexture(waterGirlTextureRight);
            if (!pushedWaterGirl && waterGirl.jumpCnt >= jumpFactor) waterGirl.move({ pixelsPerIteration , 0 });
            else if (!pushedWaterGirl) waterGirl.move({  1.825*pixelsPerIteration , 0});
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::A) && !paused && gameStarted)
        {
            waterGirl.playerSprite.setTexture(waterGirlTextureLeft);
            if (!pushedWaterGirl && waterGirl.jumpCnt >= jumpFactor) waterGirl.move({ -pixelsPerIteration , 0 });
            else if (!pushedWaterGirl) waterGirl.move({ -1.825 * pixelsPerIteration , 0 });
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::Right) && !paused && gameStarted)
        {
            fireBoy.playerSprite.setTexture(fireBoyTextureRight);
            if (!pushedFireBoy && fireBoy.jumpCnt >= jumpFactor) fireBoy.move({ pixelsPerIteration , 0 });
            else if(!pushedFireBoy)fireBoy.move({ 1.825*pixelsPerIteration , 0 });
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::Left) && !paused && gameStarted)
        {
            fireBoy.playerSprite.setTexture(fireBoyTextureLeft);
            if (!pushedFireBoy && fireBoy.jumpCnt >= jumpFactor) fireBoy.move({ -pixelsPerIteration , 0 });
            else if(!pushedFireBoy) fireBoy.move({ -1.825*pixelsPerIteration , 0 });
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

        checkMusic();   //GameControl
        gameTimer();    //GameControl

        gamePolling();  //GameControl

        window.clear();

        renderBackground(); //Render
        

        if (gameStarted && !levelInquire && !leaderboards && !currentLevelLeaderboardPage)
        {
            if(musicMute) musicLevel.stop();

            // Render door
            window.draw(spriteDoor);

            if (level != curPlatformObjectLevel)
            {
                fireBoy.Restart(), waterGirl.Restart();
                platformObjects.clear();
                platformObjects.push_back({{ground,0},0});
                fillPlatformObjects();
                fillGateObjects();
                memset(buttonGatePressed, 0, sizeof(bridgeOpened));
                memset(buttonGatePressed, 0, sizeof(buttonGatePressed));
                memset(gateOpened, 0, sizeof(gateOpened));
                curPlatformObjectLevel = level;
                deathX = deathY = -1.f;
            }

            // Render Gates
            for (auto i : gatesObjects)
            {
                if (i.first.second == 0 || i.first.second == 1 || i.first.second == 2)
                {
                    if (gateOpened[i.second] && i.first.second == 0)
                        window.draw(i.first.first);
                    else if (!gateOpened[i.second])
                        window.draw(i.first.first);
                }
                else if (i.first.second == 3 || i.first.second == 4)
                {

                    if (!bridgeOpened[i.second] && i.first.second == 3)
                        window.draw(i.first.first);
                    else if (bridgeOpened[i.second])
                        window.draw(i.first.first);
                }
            }

            // Render level
            renderLevel();

            // Check if fireboy and Watergirl is still inside the drawn borders
            fireBoy.Inquire();
            waterGirl.Inquire();

            // Render characters
            window.draw(fireBoy.playerSprite);
            window.draw(waterGirl.playerSprite);

            //Render pools
            for (auto i : platformObjects)
            {
                if (!i.second)
                    window.draw(i.first.first);
                else //Button Block
                {
                    //Gate
                    //Not interacting with current button
                    if (!waterGirl.bounds.intersects(i.first.first.getGlobalBounds()) && !fireBoy.bounds.intersects(i.first.first.getGlobalBounds()) && i.first.second == 4)
                    {
                        buttonGatePressed[i.second] = false;
                        //Checking the other gate button
                        if (i.second % 2 == 1 && !buttonGatePressed[i.second + 1])
                        {
                            gateOpened[((i.second - 1) / 2) + 1] = false;

                        }
                        if (i.second % 2 == 0 && !buttonGatePressed[i.second - 1])
                        {
                            gateOpened[((i.second - 1) / 2) + 1] = false;
                        }
                    }
                    // Opens Gate if the gate's button is pressed
                    if (i.first.second == 4 && buttonGatePressed[i.second])
                    {
                        buttonOn.setPosition(i.first.first.getPosition().x, i.first.first.getPosition().y - 20);
                        gateOpened[((i.second - 1) / 2) + 1] = true;
                        if(!gateButtonSoundPlayed[i.second])
                        {
                            buttonSound.play();
                            gateButtonSoundPlayed[i.second] = true;
                        }
                        window.draw(buttonOn);
                    }

                    if (i.first.second == 4 && !buttonGatePressed[i.second])
                    {
                        buttonOff.setPosition(i.first.first.getPosition().x, i.first.first.getPosition().y - 20);
                        window.draw(buttonOff);
                        gateButtonSoundPlayed[i.second] = false;
                    }

                    if (!waterGirl.bounds.intersects(i.first.first.getGlobalBounds()) && !fireBoy.bounds.intersects(i.first.first.getGlobalBounds()) && i.first.second == 5)
                    {
                        buttonBridgePressed[i.second] = false;
                        if (i.second % 2 == 1 && !buttonBridgePressed[i.second + 1])
                        {
                            bridgeOpened[((i.second - 1) / 2) + 1] = false;

                        }
                        else if (i.second % 2 == 0 && !buttonBridgePressed[i.second - 1])
                        {
                            bridgeOpened[((i.second - 1) / 2) + 1] = false;
                        }
                    }
                    if (i.first.second == 5 && buttonBridgePressed[i.second])
                    {

                        buttonOn.setPosition(i.first.first.getPosition().x, i.first.first.getPosition().y - 20);
                        bridgeOpened[((i.second - 1) / 2) + 1] = true;
                        if(!bridgeButtonSoundPlayed[i.second])
                        {
                            buttonSound.play();
                            bridgeButtonSoundPlayed[i.second] = true;
                        }
                        window.draw(buttonOn);
                    }
                    if (i.first.second == 5 && !buttonBridgePressed[i.second])
                    {
                        buttonOff.setPosition(i.first.first.getPosition().x, i.first.first.getPosition().y - 20);
                        window.draw(buttonOff);
                        bridgeButtonSoundPlayed[i.second] = false;
                    }
                }
            }

            // Render border
            for (int i = 0; i < 4; i++) window.draw(borders[i]);

            // Render Smoke
            if (deathCounter)
            {
                if (deathCounter < 30) { window.draw(smoke1); }
                else if (deathCounter < 60) { window.draw(smoke2); }
                else if (deathCounter < 90) { window.draw(smoke1); }
            }

            // Render timer
            window.draw(textTimer);

            // Level ending
            fireBoy.Inquire(), waterGirl.Inquire();
            float spriteDoorX = spriteDoor.getPosition().x - 20, spriteDoorY = spriteDoor.getPosition().y;
            if (fireBoy.dx >= spriteDoorX && fireBoy.dx + 80 <= spriteDoorX + 100 && fireBoy.dy <= spriteDoorY + 120 && fireBoy.dy >= spriteDoorY)
            {
                if (waterGirl.dx >= spriteDoorX && waterGirl.dx + 80 <= spriteDoorX + 100 && waterGirl.dy <= spriteDoorY + 120 && waterGirl.dy >= spriteDoorY)
                {
                    gameStarted = false;
                    levelInquire = true;
                    musicLevel.stop();
                    if (!soundFxMute) soundLevelComplete.play();
                    fireBoy.Restart();
                    waterGirl.Restart();
                    deathX = deathY = -1.f;
                    deathCounter = 0;

                    getEndingTime();    //GameControl
                }
            }

            // Render pause background
            if (gameStarted && paused)
            {
                window.draw(spritePauseBackground);
            }
        }

        if(event.type == Event::KeyReleased)
            canType = true;

        if (event.type == Event::MouseButtonReleased)
            canClick = true;

        if (fireBoy.isDead) { FBDead = 1; }
        if (waterGirl.isDead) { WGDead = 1; }



        // Get mouse position
        float mouse_xAxis = Mouse::getPosition(window).x, mouse_yAxis = Mouse::getPosition(window).y;
        if (!gameStarted && !paused && !settingsMenu && started && !bothPlayers && !levelInquire && !leaderboards && !currentLevelLeaderboardPage)
        {
            if (mouse_xAxis >= 412.5 && mouse_xAxis <= 867.5 && mouse_yAxis >= 554 && mouse_yAxis <= 596)
            {
                if (!hoverGuest)
                {
                    soundButtonHover.play();
                    hoverGuest = true;
                }
                textGuest.setFillColor(Color::Green);
                if (Mouse::isButtonPressed(Mouse::Left) && canClick)
                {
                    player1Input = true, player2Input = true;
                    bothPlayers = true, guest = true;
                    canClick = false;
                }
            }
            else {
                hoverGuest = false;
                textGuest.setFillColor(Color::White);
            }
            window.draw(textGuest);
        }

        // Player 1 Name
        if (!gameStarted && !paused && !settingsMenu && started && !bothPlayers && player1Input && !player2Input && !levelInquire && !leaderboards && !currentLevelLeaderboardPage)
        {
            window.draw(enterYourNameRectangle);
            window.draw(enterYourNameRectangle2);
            if (event.type == sf::Event::TextEntered && event.text.unicode == 8 && !player1Name.empty() && canType)
            {
                canType = false;
                player1Name.pop_back();
                player1Text.setString(player1Name);
                window.draw(player1Text);
                //continue;
            }
            else if (player1Name.size() >= 10)
            { //
            }
            else if (event.type == sf::Event::TextEntered && event.text.unicode <= 128 && event.text.unicode != 8 && !Keyboard::isKeyPressed(Keyboard::Key::Return) && canType)
            {
                canType = false;
                player1Name += tolower(event.text.unicode);
                player1Text.setString(player1Name);

            }
            // Player has entered player 1 name
            if (Keyboard::isKeyPressed(Keyboard::Key::Return) && !player1Name.empty())
            {
                player1Input = false;
                player2Input = true;
            }
            textRect = player1Text.getLocalBounds();
            player1Text.setOrigin(textRect.left +
                textRect.width / 2.0f,
                textRect.top +
                textRect.height / 2.0f);
            player1Text.setPosition(640, 350);
            window.draw(textTitle);
            window.draw(player1Text);
            Color colorEnterYourName(255, 255, 255, enterYourNameFillColor -= ((enterYourNameFillColorInc) ? -5 : 5));
            textEnterYourName.setFillColor(colorEnterYourName);
            window.draw(textEnterYourName);
        }

        // Player 2 name
        else if (!gameStarted && !paused && !settingsMenu && started && !bothPlayers && !player1Input && player2Input && !levelInquire && !leaderboards && !currentLevelLeaderboardPage)
        {
            window.draw(enterYourNameRectangle);
            window.draw(enterYourNameRectangle2);
            if (event.type == sf::Event::TextEntered && event.text.unicode == 8 && !player2Name.empty() && canType)
            {
                canType = false;
                player2Name.pop_back();
                player2Text.setString(player2Name);
                window.draw(player2Text);
                //continue;
            }
            else if (player2Name.size() >= 10)
            { //
            }
            else if (event.type == sf::Event::TextEntered && event.text.unicode <= 128 && event.text.unicode != 8 && !Keyboard::isKeyPressed(Keyboard::Key::Return) && canType)
            {
                canType = false;
                player2Name += tolower(event.text.unicode);
                player2Text.setString(player2Name);

            }
            // Player has entered player 2 name
            if (Keyboard::isKeyPressed(Keyboard::Key::Return) && !player2Name.empty())
            {
                player1Input = true, player2Input = true;
                bothPlayers = true;
            }

            window.draw(textTitle);
            window.draw(player1Text);
            window.draw(player2Text);
            Color colorEnterYourName(255, 255, 255, enterYourNameFillColor -= ((enterYourNameFillColorInc) ? -5 : 5));
            textEnterYourName.setFillColor(colorEnterYourName);
            textEnterYourName.setString("Enter player 2 name:");
            textRect = player2Text.getLocalBounds();
            player2Text.setOrigin(textRect.left +
                textRect.width / 2.0f,
                textRect.top +
                textRect.height / 2.0f);
            player2Text.setPosition(640, 450);
            window.draw(textEnterYourName);
        }

        // Leaderboards page
        if (!gameStarted && !paused && !settingsMenu && started && bothPlayers && player1Input && player2Input && !levelInquire && leaderboards && !currentLevelLeaderboardPage)
        {
            // Leaderboard text
            window.draw(textLeaderboard);

            // Back arrow
            if (mouse_xAxis >= 44 && mouse_xAxis <= 163 && mouse_yAxis >= 51 && mouse_yAxis <= 104)
            {
                if (!hoverArrowLeaderboards)
                {
                    soundButtonHover.play();
                    hoverArrowLeaderboards = true;
                }
                arrowLeaderboards.setTexture(&textureRedArrow);
                if (Mouse::isButtonPressed(Mouse::Left) && canClick)
                {
                    leaderboards = false;
                    canClick = false;
                }
            }
            else {
                hoverArrowLeaderboards = false;
                arrowLeaderboards.setTexture(&textureWhiteArrow);
            }
            window.draw(arrowLeaderboards);

            for (int i = 0; i < 10; i++) window.draw(textLevels[i]);

            for (int i = 0; i < 10; i++)
            {
                float textLevelCoordinatesW = textLevels[i].getLocalBounds().width, textLevelCoordinatesH = textLevels[i].getLocalBounds().height;
                if (mouse_xAxis >= ((i < 5) ? 440 : 840) - textLevelCoordinatesW / 2 && mouse_xAxis <= ((i < 5) ? 440 : 840) + textLevelCoordinatesW / 2 && mouse_yAxis >= ((i < 5) ? (i + 1) * 100 + 130 : (i - 5 + 1) * 100 + 130) - textLevelCoordinatesH / 2 && mouse_yAxis <= ((i < 5) ? (i + 1) * 100 + 130 : (i - 5 + 1) * 100 + 130) + textLevelCoordinatesH / 2)
                {
                    if (!hoverTextLevels[i])
                    {
                        soundButtonHover.play();
                        hoverTextLevels[i] = true;
                    }
                    textLevels[i].setFillColor(Color::Green);
                    if (Mouse::isButtonPressed(Mouse::Left) && canClick)
                    {
                        levelLeaderboardPage[i] = true;
                        canClick = false;
                        break;
                    }
                }
                else {
                    hoverTextLevels[i] = false;
                    textLevels[i].setFillColor(Color::White);
                }
            }
        }

        // Current level leaderboard page
        if (currentLevelLeaderboardPage)
        {
            // Render title for this page
            window.draw(textMainLevels[currentLevelLeaderboardPage - 1]);

            // Retrieve high scores for this level
            getTopTenOfLevel(currentLevelLeaderboardPage);

            Text currentLevelRecord;
            currentLevelRecord.setFont(fontTitle);
            currentLevelRecord.setCharacterSize(40);
            currentLevelRecord.setFillColor(Color::White);

            for (int i = 0; i < min((int)topTen.size(), 5); i++)
            {
                string levelRecordMinutes = to_string(topTen[i].first / 60), levelRecordSeconds = to_string(topTen[i].first % 60);
                if (levelRecordMinutes.size() == 1) levelRecordMinutes = "0" + levelRecordMinutes;
                if (levelRecordSeconds.size() == 1) levelRecordSeconds = "0" + levelRecordSeconds;
                currentLevelRecord.setString("#" + to_string(i + 1) + " " + topTen[i].second.first + " & " + topTen[i].second.second + " (Score: " + levelRecordMinutes + ":" + levelRecordSeconds + ")");
                currentLevelRecord.setPosition(100, (i + 1) * 100 + 100);
                window.draw(currentLevelRecord);
            }

            // Back arrow
            if (mouse_xAxis >= 44 && mouse_xAxis <= 163 && mouse_yAxis >= 51 && mouse_yAxis <= 104)
            {
                if (!hoverArrowLevelLeaderboard)
                {
                    soundButtonHover.play();
                    hoverArrowLevelLeaderboard = true;
                }
                arrowLevelLeaderboard.setTexture(&textureRedArrow);
                if (Mouse::isButtonPressed(Mouse::Left) && canClick)
                {
                    canClick = false;
                    levelLeaderboardPage[currentLevelLeaderboardPage - 1] = false;
                    currentLevelLeaderboardPage = 0;
                    leaderboards = true;
                }
            }
            else {
                hoverArrowLevelLeaderboard = false;
                arrowLevelLeaderboard.setTexture(&textureWhiteArrow);
            }
            window.draw(arrowLevelLeaderboard);
        }

        // Level inquire
        if (levelInquire && started && !gameStarted && !paused && !settingsMenu && bothPlayers && !leaderboards && !currentLevelLeaderboardPage)
        {
            // Back arrow
            if (mouse_xAxis >= 44 && mouse_xAxis <= 163 && mouse_yAxis >= 51 && mouse_yAxis <= 104)
            {
                if (!hoverArrowLevelInquire)
                {
                    soundButtonHover.play();
                    hoverArrowLevelInquire = true;
                }
                arrowLevelInquire.setTexture(&textureRedArrow);
                if (Mouse::isButtonPressed(Mouse::Left) && canClick)
                {
                    canClick = false;
                    levelInquire = false;
                }
            }
            else {
                hoverArrowLevelInquire = false;
                arrowLevelInquire.setTexture(&textureWhiteArrow);
            }
            window.draw(arrowLevelInquire);

            string currentPlayer1 = min({ player1Name, player2Name });
            string currentPlayer2 = max({ player1Name, player2Name });

            // Level 1
            window.draw(textLevel1);
            if (!gameStarted && mouse_xAxis >= 251 && mouse_xAxis <= 1029 && mouse_yAxis >= 268.5 && mouse_yAxis <= 331.5)
            {
                if (!hoverLevel1)
                {
                    soundButtonHover.play();
                    hoverLevel1 = true;
                }
                textLevel1.setFillColor(Color::Green);
                if (Mouse::isButtonPressed(Mouse::Left) && canClick)
                {
                    level = 0;
                    canClick = false;
                    spriteDoor.setPosition(1160, 95);
                    gameStarted = true, levelInquire = false;
                    musicIntro.stop();
                    musicLevel.play();
                    chron.reset(), chron.resume();
                }
            }
            else {
                hoverLevel1 = false;
                textLevel1.setFillColor(Color::White);
            }
            // Level 2
            window.draw(textLevel2);
            if (!gameStarted && mouse_xAxis >= 237 && mouse_xAxis <= 1043 && mouse_yAxis >= 418.5 && mouse_yAxis <= 481.5)
            {
                if ((!guest && currentRecords[{currentPlayer1, currentPlayer2}].size() > 0 && currentRecords[{currentPlayer1, currentPlayer2}][0]) || (guest && guestRecords[0]))
                {
                    if (!hoverLevel2)
                    {
                        soundButtonHover.play();
                        hoverLevel2 = true;
                    }
                    textLevel2.setFillColor(Color::Green);
                    if (Mouse::isButtonPressed(Mouse::Left) && canClick)
                    {
                        canClick = false;
                        level = 1;
                        spriteDoor.setPosition(120, 95);
                        gameStarted = true, levelInquire = false;
                        musicIntro.stop();
                        musicLevel.play();
                        chron.reset(), chron.resume();
                    }
                }
            }
            else {
                hoverLevel2 = false;
                textLevel2.setFillColor(Color::White);
            }
        }


        if (!gameStarted && !paused && !settingsMenu && started && bothPlayers && !levelInquire && !leaderboards && !currentLevelLeaderboardPage)
        {
            // Render text title
            window.draw(textTitle);

            // Start button
            if (!gameStarted && mouse_xAxis >= 561 && mouse_xAxis <= 719 && mouse_yAxis >= 279 && mouse_yAxis <= 321)
            {
                if (!hoverStart)
                {
                    soundButtonHover.play();
                    hoverStart = true;
                }
                textStart.setFillColor(Color::Green);
                if (Mouse::isButtonPressed(Mouse::Left) && canClick)
                {
                    canClick = false;
                    levelInquire = true;
                    chron.reset(), chron.resume();
                }
            }
            else {
                hoverStart = false;
                textStart.setFillColor(Color::White);
            }
            window.draw(textStart);

            // Leaderboards button
            if (!gameStarted && mouse_xAxis >= 447.5 && mouse_xAxis <= 832.5 && mouse_yAxis >= 479 && mouse_yAxis <= 521)
            {
                if (!hoverLeaderboards)
                {
                    soundButtonHover.play();
                    hoverLeaderboards = true;
                }
                textLeaderboards.setFillColor(Color::Green);
                if (Mouse::isButtonPressed(Mouse::Left) && canClick)
                {
                    canClick = false;
                    leaderboards = true;
                }
            }
            else {
                hoverLeaderboards = false;
                textLeaderboards.setFillColor(Color::White);
            }
            window.draw(textLeaderboards);
        }

        bool oneDead = (FBDead || WGDead);

        if (!gameStarted || paused || settingsMenu || leaderboards || currentLevelLeaderboardPage)
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
                if (Mouse::isButtonPressed(Mouse::Left) && canClick)
                {
                    canClick = false;
                    window.close();
                }
            }
            else {
                hoverExit = false;
                textExit.setFillColor(Color::White);
            }
            window.draw(textExit);
        }

        if ((paused || !gameStarted) && !settingsMenu && started && bothPlayers && !levelInquire && !leaderboards && !currentLevelLeaderboardPage)
        {

            // Settings Button
            if (mouse_xAxis >= 518 && mouse_xAxis <= 760 && mouse_yAxis >= ((oneDead || !gameStarted) ? 383 : 483) && mouse_yAxis <= ((oneDead || !gameStarted) ? 420 : 520))
            {
                if (!hoverSettings)
                {
                    soundButtonHover.play();
                    hoverSettings = true;
                }
                textSettings.setFillColor(Color::Green);
                if (Mouse::isButtonPressed(Mouse::Left) && canClick)
                {
                    canClick = false;
                    settingsMenu = true;
                }
            }
            else {
                hoverSettings = false;
                textSettings.setFillColor(Color::White);
            }
            if (oneDead || !gameStarted) textSettings.setPosition(640, 400);
            else textSettings.setPosition(640, 500);
            window.draw(textSettings);
        }



        if (paused && !settingsMenu && started && !levelInquire && !leaderboards && !currentLevelLeaderboardPage)
        {
            // Render text paused
            if (!FBDead && !WGDead) window.draw(textPaused);

            // Render text game over
            if (FBDead || WGDead) window.draw(textGameOver);

            // Continue button
            if (!FBDead && !WGDead)
            {
                if (mouse_xAxis >= 278.5 && mouse_xAxis <= 1001.5 && mouse_yAxis >= 278.5 && mouse_yAxis <= 321.5)
                {
                    if (!hoverContinue)
                    {
                        soundButtonHover.play();
                        hoverContinue = true;
                    }
                    textContinue.setFillColor(Color::Green);
                    if (Mouse::isButtonPressed(Mouse::Left) && canClick)
                    {
                        canClick = false;
                        paused = false, chron.resume();
                    }
                }
                else {
                    hoverContinue = false;
                    textContinue.setFillColor(Color::White);
                }
                window.draw(textContinue);
            }
            // Retry level Button
            if (mouse_xAxis >= 476.5 && mouse_xAxis <= 803.5 && mouse_yAxis >= ((oneDead) ? 279 : 379) && mouse_yAxis <= ((oneDead) ? 321 : 421))
            {
                if (!hoverRetry)
                    hoverRetry = true;

                textRetryLevel.setFillColor(Color::Green);
                if (Mouse::isButtonPressed(Mouse::Left) && canClick)
                {
                    canClick = false;
                    waterGirl.Restart(), fireBoy.Restart();
                    chron.reset(), chron.resume(), paused = false;
                    musicLevel.stop(), musicLevel.play();
                    deathX = deathY = -1.f;
                    deathCounter = 0;
                }
            }
            else {
                hoverRetry = false;
                textRetryLevel.setFillColor(Color::White);
            }
            if (oneDead) textRetryLevel.setPosition(640, 300);
            else textRetryLevel.setPosition(640, 400);
            window.draw(textRetryLevel);

            // Main menu button
            if (mouse_xAxis >= 516.5 && mouse_xAxis <= 763.5 && mouse_yAxis >= ((oneDead) ? 478.5 : 578.5) && mouse_yAxis <= ((oneDead) ? 521.5 : 621.5))
            {
                if (!hoverMainMenu)
                {
                    soundButtonHover.play();
                    hoverMainMenu = true;
                }
                textMainMenu.setFillColor(Color::Green);
                if (Mouse::isButtonPressed(Mouse::Left) && canClick)
                {
                    canClick = false;
                    gameStarted = false, paused = false;
                    fireBoy.Restart(), waterGirl.Restart();
                    musicLevel.stop();
                    deathX = deathY = -1.f;
                    deathCounter = 0;
                }
            }
            else {
                hoverMainMenu = false;
                textMainMenu.setFillColor(Color::White);
            }
            if (oneDead) textMainMenu.setPosition(640, 500);
            else textMainMenu.setPosition(640, 600);
            window.draw(textMainMenu);
        }if (settingsMenu && started && !levelInquire && !leaderboards && !currentLevelLeaderboardPage)
        {
            Text state1, state2;

            if (musicMute)
                state1 = textOff;
            else
                state1 = textOn;

            if (soundFxMute)
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
                if (musicMute)
                {
                    state1 = textOff;
                    state1.setFillColor(Color::Green);
                }
                else
                {
                    state1 = textOn;
                    state1.setFillColor(Color::Red);
                }
                if (Mouse::isButtonPressed(Mouse::Left) && !pressedMusicMute && canClick)
                {
                    if (musicMute)
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
                    canClick = false;
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
                if (soundFxMute)
                {
                    state2 = textOff;
                    state2.setFillColor(Color::Green);
                }
                else
                {
                    state2 = textOn;
                    state2.setFillColor(Color::Red);
                }
                if (Mouse::isButtonPressed(Mouse::Left) && !pressedSoundFxMute && canClick)
                {
                    if (soundFxMute)
                        soundFxMute = false;
                    else
                        soundFxMute = true;

                    canClick = false;
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
                if (Mouse::isButtonPressed(Mouse::Left) && canClick)
                {
                    canClick = false;
                    settingsMenu = false;
                }
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
                if (Mouse::isButtonPressed(Mouse::Left) && canClick)
                {
                    canClick = false;
                    started = true, player1Input = true;
                }
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
