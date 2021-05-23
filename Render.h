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
#include "Visuals.h"
#include "GameControl.h"
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

void renderPauseBackground()
{
    if (gameStarted && paused)
    {
        window.draw(spritePauseBackground);
    }
}

// Render intro page
void renderIntro()
{
    // Get mouse coordinates
    getMouseCoordinates();

    // Fill bool
    fillBool();

    if (!started)
    {
        // Flag to check if currently hovering
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
                // Dont accept new input till released
                canClick = false;

                // Go to start menu
                started = true;
                player1Input = true;
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

        // Render intro text (Visuals)
        window.draw(textIntro);

        // Render continue intro text (Visuals)
        window.draw(textContinueIntro);
    }
}

// Main menu page
void renderMainMenu()
{
    if (mainMenu)
    {
        // Render text title (Visuals)
        window.draw(textTitle);
        Sprite menuBackGround;
        menuBackGround.setTexture(textureMenuBackground);
        window.draw(menuBackGround);

        // Theme button
        window.draw(textThemesButton);
        if(mouse_xAxis >= 550 && mouse_xAxis <= 740 && mouse_yAxis >= 570 && mouse_yAxis <= 620)
        {
            if(!hoverTheme)
            {
                soundButtonHover.play();
                hoverTheme = true;
                textThemesButton.setFillColor(Color::Green);
            }
            if(Mouse::isButtonPressed(Mouse::Left) && canClick)
            {
                themeMenu = true;
                mainMenu = false;
            }
        }
        else
        {
            textThemesButton.setFillColor(Color::White);
            hoverTheme = false;
        }

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
                // Dont accept new input till released
                canClick = false;

                // Go to level inquire page
                levelInquire = true;

                // Reset the timer
                chron.reset();

                // Start the timer
                chron.resume();
            }
        }
        else {
            hoverStart = false;
            textStart.setFillColor(Color::White);
        }

        // Render "Start" text (Visuals)
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
                // Dont accept new input till released
                canClick = false;

                // Go to leaderboards page
                leaderboards = true;
            }
        }
        else {
            hoverLeaderboards = false;
            textLeaderboards.setFillColor(Color::White);
        }

        // Render "Leaderboard" text (Visuals)
        window.draw(textLeaderboards);
    }
}

// Level inquire page
void renderLevelInquire()
{
    if (levelInquire)
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
                // Dont accept new input till released
                canClick = false;

                // Go back to the start menu
                levelInquire = false;
            }
        }
        else {
            hoverArrowLevelInquire = false;
            arrowLevelInquire.setTexture(&textureWhiteArrow);
        }

        // Render back arrow (Visuals)
        window.draw(arrowLevelInquire);

        // Render title of this page (Visuals)
        window.draw(textLevelsTitle);

        string currentPlayer1 = min({ player1Name, player2Name });
        string currentPlayer2 = max({ player1Name, player2Name });

        // Render 10 leaderboard levels as options (Visuals)
        for (int i = 0; i < 10; i++) window.draw(textLevels[i]);

        // Loop on all 10 level texts to hover and check for mouse clicks
        for (int i = 0; i < 10; i++)
        {
            // Calculate width and height of the level # text
            float textLevelCoordinatesW = textLevels[i].getLocalBounds().width, textLevelCoordinatesH = textLevels[i].getLocalBounds().height;
            if (((currentRecords[{currentPlayer1, currentPlayer2}].size() >= i && (i == 0 || currentRecords[{currentPlayer1, currentPlayer2}][i - 1] != 0)) || (guestRecords.size() >= i && guest && (i == 0 || guestRecords[i - 1] != 0))) && mouse_xAxis >= ((i < 5) ? 440 : 840) - textLevelCoordinatesW / 2 && mouse_xAxis <= ((i < 5) ? 440 : 840) + textLevelCoordinatesW / 2 && mouse_yAxis >= ((i < 5) ? (i + 1) * 100 + 130 : (i - 5 + 1) * 100 + 130) - textLevelCoordinatesH / 2 && mouse_yAxis <= ((i < 5) ? (i + 1) * 100 + 130 : (i - 5 + 1) * 100 + 130) + textLevelCoordinatesH / 2)
            {
                if (!hoverTextLevels[i])
                {
                    soundButtonHover.play();
                    hoverTextLevels[i] = true;
                }
                textLevels[i].setFillColor(Color::Green);
                if (Mouse::isButtonPressed(Mouse::Left) && canClick)
                {
                    // Start the level
                    level = i;
                    chron.resume();
                    gameStarted = true;
                    levelInquire = false;

                    if (!musicMute)
                    {
                        musicIntro.stop();
                        musicLevel.play();
                    }

                    // Dont accept new input till released
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
}

// Enter your name or play as a guest page
void renderEnterYourName()
{
    if (started && !bothPlayers)
    {
        Sprite menuBackGround;
        menuBackGround.setTexture(textureMenuBackground);
        window.draw(menuBackGround);

        // Guest button
        if (mouse_xAxis >= 412.5 && mouse_xAxis <= 867.5 && mouse_yAxis >= 554 && mouse_yAxis <= 596)
        {
            if (!hoverGuest)
            {
                soundButtonHover.play();
                hoverGuest = true;
            }
            textGuest.setFillColor(Color::Green);
            // Play as a guest is pressed
            if (Mouse::isButtonPressed(Mouse::Left) && canClick)
            {
                // Mark player input as done (Its not in reality)
                player1Input = true;
                player2Input = true;
                bothPlayers = true;

                // Move the player through the game as a guest
                guest = true;

                // Dont accept new input till released
                canClick = false;
            }
        }
        else {
            hoverGuest = false;
            textGuest.setFillColor(Color::White);
        }

        // Draw "Play as a guest" text (Visuals)
        window.draw(textGuest);
    }
}

// Taking first player name
void renderFirstPlayerName()
{
    if (player1Input && !bothPlayers)
    {
        // Render input boxes (Visuals)
        window.draw(enterYourNameRectangle);
        window.draw(enterYourNameRectangle2);

        // Detect backspace key pressed
        if (event.type == sf::Event::TextEntered && event.text.unicode == 8 && !player1Name.empty() && canType)
        {
            // Dont accept new input till released
            canType = false;

            // Remove the last character
            player1Name.pop_back();

            // Set the name as player one name
            player1Text.setString(player1Name);

            // Render player one name
            window.draw(player1Text);
        }
            // Max name size is 10 characters
        else if (player1Name.size() >= 10) {}
            // Adding new characters to the player's name
        else if (event.type == sf::Event::TextEntered && event.text.unicode <= 128 && event.text.unicode != 8 && !Keyboard::isKeyPressed(Keyboard::Key::Return) && canType)
        {
            // Dont accept new input till released
            canType = false;

            // Add the new entered characters to the name
            player1Name += tolower(event.text.unicode);

            // Set the name as player one name
            player1Text.setString(player1Name);

        }
        // Player one name is entered
        if (Keyboard::isKeyPressed(Keyboard::Key::Return) && !player1Name.empty())
        {
            // Disable input to player one input box
            player1Input = false;

            // Enable input to player two input box
            player2Input = true;
        }

        // Setting origin to the middle of the text
        textRect = player1Text.getLocalBounds();
        player1Text.setOrigin(textRect.left +
                              textRect.width / 2.0f,
                              textRect.top +
                              textRect.height / 2.0f);

        // Setting position to middle of the screen
        player1Text.setPosition(640, 350);

        // Rendering the title (Visuals)
        window.draw(textTitle);

        // Rendering player one name (Visuals)
        window.draw(player1Text);

        // Applying fade to the text
        Color colorEnterYourName(255, 255, 255, enterYourNameFillColor -= ((enterYourNameFillColorInc) ? -5 : 5));
        textEnterYourName.setFillColor(colorEnterYourName);

        // Rendering "Enter player 1 name" text (Visuals)
        window.draw(textEnterYourName);
    }
}

// Taking second player name
void renderSecondPlayerName()
{
    if (player2Input && !bothPlayers)
    {
        // Render input boxes (Visuals)
        window.draw(enterYourNameRectangle);
        window.draw(enterYourNameRectangle2);

        // Detect backspace key pressed
        if (event.type == sf::Event::TextEntered && event.text.unicode == 8 && !player2Name.empty() && canType)
        {
            // Dont accept new input till released
            canType = false;

            // Remove the last character
            player2Name.pop_back();

            // Set the name as player two name
            player2Text.setString(player2Name);

            // Render player two name
            window.draw(player2Text);
        }
            // Max name size is 10 characters
        else if (player2Name.size() >= 10) {}
            // Adding new characters to the player's name
        else if (event.type == sf::Event::TextEntered && event.text.unicode <= 128 && event.text.unicode != 8 && !Keyboard::isKeyPressed(Keyboard::Key::Return) && canType)
        {
            // Dont accept new input till released
            canType = false;

            // Add the new entered characters to the name
            player2Name += tolower(event.text.unicode);

            // Set the name as player two name
            player2Text.setString(player2Name);
        }
        // Player two name is entered
        if (Keyboard::isKeyPressed(Keyboard::Key::Return) && !player2Name.empty())
        {
            // Disable input to player two input box
            player2Input = false;

            // Flag both names as accepted
            bothPlayers = true;
        }

        // Render title (Visuals)
        window.draw(textTitle);

        // Render player one name (Visuals)
        window.draw(player1Text);

        // Render player two name (Visuals)
        window.draw(player2Text);

        // Apply fade to the text
        Color colorEnterYourName(255, 255, 255, enterYourNameFillColor -= ((enterYourNameFillColorInc) ? -5 : 5));
        textEnterYourName.setFillColor(colorEnterYourName);

        // Setting new text to enter player's name text
        textEnterYourName.setString("Enter player 2 name:");

        // Setting origin to the middle
        textRect = player2Text.getLocalBounds();
        player2Text.setOrigin(textRect.left +
                              textRect.width / 2.0f,
                              textRect.top +
                              textRect.height / 2.0f);

        // Setting text to the middle of the screen
        player2Text.setPosition(640, 450);

        // Rendering "Enter player 2 name" text (Visuals)
        window.draw(textEnterYourName);
    }
}

// Settings button
void renderSettingsButton()
{
    if (paused && !settingsMenu || mainMenu)
    {
        // Settings Button
        if (mouse_xAxis >= 518 && mouse_xAxis <= 760 && mouse_yAxis >= ((oneDead || !gameStarted) ? 383 : 483) && mouse_yAxis <= ((oneDead || !gameStarted) ? 420 : 520))
        {
            if (!hoverSettings)
            {
                soundButtonHover.play();
                hoverSettings = true;
            }
            textSettingsButton.setFillColor(Color::Green);
            if (Mouse::isButtonPressed(Mouse::Left) && canClick)
            {
                // Dont accept new input till released
                canClick = false;

                // Go to settings menu page
                settingsMenu = true;
            }
        }
        else {
            hoverSettings = false;
            textSettingsButton.setFillColor(Color::White);
        }

        // Different positions for settings text in different page
        if (oneDead || !gameStarted) textSettingsButton.setPosition(640, 400);
        else textSettingsButton.setPosition(640, 500);

        // Render "Settings" text (Visuals)
        window.draw(textSettingsButton);
    }
}

// Exit button
void renderExit()
{
    if (!(gameStarted && !paused))
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
                // Dont accept new input till released
                canClick = false;

                // Close the window
                window.close();
            }
        }
        else {
            hoverExit = false;
            textExit.setFillColor(Color::White);
        }

        // Render "Exit" text (Visuals)
        window.draw(textExit);
    }
}

// Leaderboards page
void renderLeaderboards()
{
    if (leaderboards)
    {
        // Render leaderboard text (Visuals)
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
                // Go back to the start menu
                leaderboards = false;

                // Dont accept new input till released
                canClick = false;
            }
        }
        else {
            hoverArrowLeaderboards = false;
            arrowLeaderboards.setTexture(&textureWhiteArrow);
        }

        // Render back arrow (Visuals)
        window.draw(arrowLeaderboards);

        // Render 10 leaderboard levels as options (Visuals)
        for (int i = 0; i < 10; i++) window.draw(textLevels[i]);

        // Loop on all 10 level texts to hover and check for mouse clicks
        for (int i = 0; i < 10; i++)
        {
            // Calculate width and height of the level # text
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
                    // Send him to the level leaderboard page
                    levelLeaderboardPage[i] = true;

                    // Dont accept new input till released
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
}

// Current level leaderboard page
void renderCurrentLevelLeaderboard()
{
    if (currentLevelLeaderboardPage)
    {
        // Render title for this page (Visuals)
        window.draw(textMainLevels[currentLevelLeaderboardPage - 1]);

        // Retrieve high scores for this level (Data retrieval)
        getTopTenOfLevel(currentLevelLeaderboardPage);

        // Each record text
        Text currentLevelRecord;
        currentLevelRecord.setFont(fontTitle);
        currentLevelRecord.setCharacterSize(40);
        currentLevelRecord.setFillColor(Color::White);

        // Show at most 5 top records
        for (int i = 0; i < min((int)topTen.size(), 5); i++)
        {
            // Convert seconds and minutes to strings
            string levelRecordMinutes = to_string(topTen[i].first / 60), levelRecordSeconds = to_string(topTen[i].first % 60);

            // Add an extra 0 in the begging if the length of the seconds or the minutes are one
            if (levelRecordMinutes.size() == 1) levelRecordMinutes = "0" + levelRecordMinutes;
            if (levelRecordSeconds.size() == 1) levelRecordSeconds = "0" + levelRecordSeconds;

            // Setting string to current record
            currentLevelRecord.setString("#" + to_string(i + 1) + " " + topTen[i].second.first + " & " + topTen[i].second.second + " (Score: " + levelRecordMinutes + ":" + levelRecordSeconds + ")");

            // Setting position to current record
            currentLevelRecord.setPosition(100, (i + 1) * 100 + 100);

            // Rendering current record to the screen
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
                // Dont accept new input till released
                canClick = false;

                // Go back to leaderboards page
                levelLeaderboardPage[currentLevelLeaderboardPage - 1] = false;
                currentLevelLeaderboardPage = 0;
                leaderboards = true;
            }
        }
        else {
            hoverArrowLevelLeaderboard = false;
            arrowLevelLeaderboard.setTexture(&textureWhiteArrow);
        }

        // Render back arrow (Visuals)
        window.draw(arrowLevelLeaderboard);
    }
}

// Settings page
void renderSettings()
{
    if (settingsMenu)
    {
        // Music and soundFX text states
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
            // Remove the extra condition if the game works fine
            if (Mouse::isButtonPressed(Mouse::Left) /*&& !pressedMusicMute*/ && canClick)
            {
                // If it was muted and got turned on
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

                // Dont accept new input till released
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
            // Remove the extra condition if the game works fine
            if (Mouse::isButtonPressed(Mouse::Left) /*&& !pressedSoundFxMute*/ && canClick)
            {
                // If soundFX was muted and go turned on
                if (soundFxMute)
                    soundFxMute = false;
                else
                    soundFxMute = true;

                // Dont accept new input till released
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
                // Dont accept new input till released
                canClick = false;

                // Go back to start menu
                settingsMenu = false;
            }
        }
        else {
            hoverSoundFxMute = false;
            arrow.setTexture(&textureWhiteArrow);
        }

        // Setting positions for ON/OFF music text
        state1.setPosition(740, 300);

        // Setting positions for ON/OFF soundFX text
        state2.setPosition(785, 400);

        // Render "Music" text (Visuals)
        window.draw(textMusic);

        // Render "SoundFX" text (Visuals)
        window.draw(textSoundFx);

        // Render "ON/OFF" music text (Visuals)
        window.draw(state1);

        // Render "ON/OFF" soundFX text (Visuals)
        window.draw(state2);

        // Render back arrow (Visuals)
        window.draw(arrow);

        // Render Title
        window.draw(textSettingsTitle);
    }
}

// Themes page
void renderTheme()
{
    if(themeMenu)
    {
        // Title
        window.draw(textThemesTitle);

        if(stone)
            textStone.setFillColor(Color::Green);
        else
            textStone.setFillColor(Color::White);

        if(sand)
            textSand.setFillColor(Color::Green);
        else
            textSand.setFillColor(Color::White);

        if(mouse_xAxis >= 573 && mouse_xAxis <= 707 && mouse_yAxis >= 276.5 && mouse_yAxis <= 323.5) //Sand
        {
            if(!hoverSand)
            {
                hoverSand = true;
                soundButtonHover.play();
            }
            if(Mouse::isButtonPressed(Mouse::Left) && canClick)
            {
                sand = true;
                stone = false;
                canClick = false;
            }
        }
        else
            hoverSand = false;

        if(mouse_xAxis >= 552.5 && mouse_xAxis <= 727.5 && mouse_yAxis >= 378 && mouse_yAxis <= 422) //Stone
        {
            if(!hoverStone)
            {
                hoverStone = true;
                soundButtonHover.play();
            }
            if(Mouse::isButtonPressed(Mouse::Left) && canClick)
            {
                sand = false;
                stone = true;
                canClick = false;
            }
        }
        else
            hoverStone = false;

        window.draw(textSand);
        window.draw(textStone);
        // Back Arrow
        if (mouse_xAxis >= 44 && mouse_xAxis <= 163 && mouse_yAxis >= 51 && mouse_yAxis <= 104)
        {
            if (!hoverArrowThemes)
            {
                soundButtonHover.play();
                hoverArrowThemes = true;
            }
            arrowThemes.setTexture(&textureRedArrow);
            if (Mouse::isButtonPressed(Mouse::Left) && canClick)
            {
                // Dont accept new input till released
                canClick = false;
                // Go back to the start menu
                themeMenu = false;
            }
        }
        else {
            hoverArrowThemes = false;
            arrowThemes.setTexture(&textureWhiteArrow);
        }
        window.draw(arrowThemes);
    }
}
// Paused page
void renderPaused(Player& fireBoy, Player& waterGirl)
{
    if (paused && !settingsMenu)
    {
        // Render "Paused" text (Visuals)
        if (!FBDead && !WGDead) window.draw(textPaused);

        // Render "Game over" text (Visuals)
        if (FBDead || WGDead) window.draw(textGameOver);

        // Continue button
        // Only render it in case they are both alive
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
                    // Dont accept new input till released
                    canClick = false;

                    // Continue the level
                    paused = false;

                    // Resume the timer
                    chron.resume();
                }
            }
            else {
                hoverContinue = false;
                textContinue.setFillColor(Color::White);
            }

            // Render "Continue" text (Visuals)
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
                // Dont accept new input till released
                canClick = false;

                // Restart both characters
                fireBoy.Restart();
                waterGirl.Restart();
                FBDead = 0, WGDead = 0;

                // Restart enemies
                restartEnemies();

                // Reset the timer
                chron.reset();

                // Start the timer
                chron.resume();

                // Start the level from the beginning
                paused = false;

                // Restart level music
                musicLevel.stop();
                musicLevel.play();

                // Restart boxes
                boxesRestart();

                // Reset death counter
                deathX = deathY = -100.f;
                deathCounter = 0;

                // Clear gems boolean array
                restartGems();
            }
        }
        else {
            hoverRetry = false;
            textRetryLevel.setFillColor(Color::White);
        }

        // Positions differ from one page to another
        if (oneDead) textRetryLevel.setPosition(640, 300);
        else textRetryLevel.setPosition(640, 400);

        // Render "Retry level" text (Visuals)
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
                // Dont accept new input till released
                canClick = false;

                // Go to start menu
                gameStarted = false;
                paused = false;

                // Restart both characters (Players)
                fireBoy.Restart();
                waterGirl.Restart();
                FBDead = 0, WGDead = 0;

                // Restart enemies
                restartEnemies();

                // Stop level music
                musicLevel.stop();

                // Reset death counter
                deathX = deathY = -100.f;
                deathCounter = 0;
            }
        }
        else {
            hoverMainMenu = false;
            textMainMenu.setFillColor(Color::White);
        }

        // Positions differ from one page to another
        if (oneDead) textMainMenu.setPosition(640, 500);
        else textMainMenu.setPosition(640, 600);

        // Render "Main menu" text (Visuals)
        window.draw(textMainMenu);
    }
}

// Pools
void renderPools(Player& fireBoy, Player& waterGirl)
{
    for (auto i : platformObjects)
    {
        if (!i.second)
            window.draw(i.first.first);
        else // Button block
        {
            // Gate
            // Not interacting with current button
            bool boxButtonGatePressed = false;
            if (!waterGirl.bounds.intersects(i.first.first.getGlobalBounds()) && !fireBoy.bounds.intersects(i.first.first.getGlobalBounds()) && i.first.second == 4)
            {
               
                for(int j = 0;j < boxes.size();++j)
                {
                    if (abs(i.first.first.getPosition().y - boxes[j].getPosition().y) <= 82 && abs(boxes[j].getPosition().x - i.first.first.getPosition().x) <= 42)
                    {
                            boxButtonGatePressed = true;
                            buttonGatePressed[i.second] = true;
                            break;
                    }
                }
                if(!boxButtonGatePressed)
                {
                    buttonGatePressed[i.second] = false;
                    // Checking the other gate button
                    if (i.second % 2 == 1 && !buttonGatePressed[i.second + 1])
                    {
                        gateOpened[((i.second - 1) / 2) + 1] = false;
                    }
                    if (i.second % 2 == 0 && !buttonGatePressed[i.second - 1])
                    {
                        gateOpened[((i.second - 1) / 2) + 1] = false;
                    }
                }
                
            }

            // Opens Gate if the gate's button is pressed
            if (i.first.second == 4 && buttonGatePressed[i.second])
            {
                if (!gateButtonSoundPlayed[i.second] && !soundFxMute)
                {
                    buttonSound.play();
                    gateButtonSoundPlayed[i.second] = true;
                }
                buttonOn.setPosition(i.first.first.getPosition().x, i.first.first.getPosition().y - 20);
                gateOpened[((i.second - 1) / 2) + 1] = true;
                window.draw(buttonOn);
            }

            if (i.first.second == 4 && !buttonGatePressed[i.second])
            {
                gateButtonSoundPlayed[i.second] = false;
                buttonOff.setPosition(i.first.first.getPosition().x, i.first.first.getPosition().y - 20);
                window.draw(buttonOff);
            }
            // Buttons for bridges
            if (!waterGirl.bounds.intersects(i.first.first.getGlobalBounds()) && !fireBoy.bounds.intersects(i.first.first.getGlobalBounds()) && i.first.second == 5)
            {
                bool boxButtonBridgePressed = false;
                for(int j = 0;j < boxes.size();++j)
                {
                    if (abs(i.first.first.getPosition().y - boxes[j].getPosition().y) <= 82 && abs(boxes[j].getPosition().x - i.first.first.getPosition().x) <= 42)
                    {
                        boxButtonBridgePressed = true;
                        buttonBridgePressed[i.second] = true;
                        break;
                    }
                }
                if(!boxButtonBridgePressed)
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
               
            }

            if (i.first.second == 5 && buttonBridgePressed[i.second])
            {
                if (!bridgeButtonSoundPlayed[i.second] && !soundFxMute)
                {
                    buttonSound.play();
                    bridgeButtonSoundPlayed[i.second] = true;
                }
                buttonOn.setPosition(i.first.first.getPosition().x, i.first.first.getPosition().y - 20);
                bridgeOpened[((i.second - 1) / 2) + 1] = true;
                window.draw(buttonOn);
            }

            if (i.first.second == 5 && !buttonBridgePressed[i.second])
            {
                bridgeButtonSoundPlayed[i.second] = false;
                buttonOff.setPosition(i.first.first.getPosition().x, i.first.first.getPosition().y - 20);
                window.draw(buttonOff);
            }
        }
    }
}

// Borders
void renderBorders()
{
    for (int i = 0; i < 4; i++) window.draw(borders[i]);
}

// Smoke
void renderSmoke()
{
    if (deathCounter && deathX > 0)
    {
        if (deathCounter < 30)
        {
            window.draw(smoke1);
        }
        else if (deathCounter < 60)
        {
            window.draw(smoke2);
        }
        else if (deathCounter < 90)
        {
            window.draw(smoke1);
        }
    }
}

// Render timer
void renderTimer()
{
    window.draw(textTimer);
}

// Render level ending
void renderLevelEnding(Player& fireBoy, Player& waterGirl)
{
    // Get X and Y positions for fireboy and check if it has collided with the border (Players)
    fireBoy.Inquire();
    waterGirl.Inquire();

    // Door X and Y positions
    float spriteDoorX = spriteDoor.getPosition().x - 20, spriteDoorY = spriteDoor.getPosition().y;
    if (fireBoy.dx >= spriteDoorX && fireBoy.dx + 80 <= spriteDoorX + 100 && fireBoy.dy <= spriteDoorY + 120 && fireBoy.dy >= spriteDoorY)
    {
        if (waterGirl.dx >= spriteDoorX && waterGirl.dx + 80 <= spriteDoorX + 100 && waterGirl.dy <= spriteDoorY + 120 && waterGirl.dy >= spriteDoorY)
        {
            // Stop the level
            gameStarted = false;

            // Ask for a new level to play
            levelInquire = true;

            // Stop level music (Visuals)
            musicLevel.stop();

            // Check if not on mute to play level complete sound effect (Visuals)
            if (!soundFxMute) soundLevelComplete.play();

            // Reset characters (Players)
            fireBoy.Restart();
            waterGirl.Restart();

            // Restart enemies
            restartEnemies();

            // Reset death counter
            deathX = deathY = -100.f;
            deathCounter = 0;

            // Update scores with ending time (Game controls)
            getEndingTime();
            chron.reset();
        }
    }
}

// Render characters
void renderCharacters(Player& fireBoy, Player& waterGirl)
{
    window.draw(fireBoy.playerSprite);
    window.draw(waterGirl.playerSprite);
}

// Render gates
void renderGates()
{
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
}

// Render gems
void renderGems()
{
    for (auto i : gemObjects)
    {
        if (!gemsTaken[i.second])
            window.draw(i.first.first);
    }
}

// Render door
void renderDoor()
{
    window.draw(spriteDoor);
}

// Render enemies
void renderEnemies()
{
    for (auto i : enemies)
    {
        window.draw(i.first);
    }
}

// Render boxes
void renderBoxes()
{
    for (int i = 0; i < boxes.size(); ++i)
    {
        window.draw(boxes[i]);
    }
}
