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
string mHolder = "/Users/pluto/Desktop/Fireboy-And-Watergirl/";
string m = "";

// decraing text strings
string introText = "";

// loading intro text
void loadText()
{
    string temp;
    ifstream introFile;
    introFile.open(m + "assets/textData/introText.txt");

    if (!introFile.fail())
    {
        while (!introFile.eof())
        {
            getline(introFile, temp);
            introText += temp;
            introText += '\n';
        }
    }
}

void split_to_string( vector<string> &vec ,string &str, char splitter)
{
    string one_word = " ";
    for (char c : str)
    {
        if (c == splitter) { vec.push_back(one_word);one_word = " ";}
        else {one_word +=  c;}
    }
    vec.push_back(one_word);
}

int char_to_int(char c) {return (c-'0');}

int str_to_int(string &str)
{
    if (str.length() == 1) {return char_to_int(str[0]);}
    stringstream ans(str);
    int x = 0;
    ans >> x;
    return x;
}

void writeData(string data)
{
    string newData = "";
    string temp;

    fstream csvData;
    csvData.open("assets/scores.csv");

    vector<string> newRecord;
    split_to_string(newRecord,data,',');

    bool found;
    bool levelExist;
    bool newRecordFound;
    bool nameFound = false;
    while (getline(csvData,temp))
    {
        found = false;
        vector<string> currRecord;
        split_to_string(currRecord,temp,',');

//        given that the pair of names is sorted so <a,b> is same as <b,a> because both of them will be <a,b>
        if(currRecord[0] == newRecord[0])
        {
            newData += currRecord[0];
            newData += ',';

            found = true;
            nameFound = true;
            newRecordFound = false;
            vector<string> tempNewRecord;
            split_to_string(tempNewRecord,newRecord[1],'-');
            for (int i = 1 ; i < currRecord.size() ; i++)
            {
                levelExist = false;
                vector<string> tempCurrRecord;
                split_to_string(tempCurrRecord,currRecord[i],'-');

//                given that the levels are sorted
                if (tempCurrRecord[0] == tempNewRecord[0])
                {
                    levelExist = true;
                    newRecordFound = true;
                    if (str_to_int(tempCurrRecord[1]) >  str_to_int(tempNewRecord[1]))
                    {
                        newData += newRecord[1];
                        newData += ',';
                    }
                    else
                    {
                        newData += currRecord[i];
                        newData += ',';
                    }

                }
                if (!levelExist)
                {
                    newData += currRecord[i];
                    newData += ',';
                }
            }
            if (!newRecordFound)
            {
                newData += newRecord[1];
                newData += ',';
            }
        }
        if (!found)
        {
            newData += temp ;
        }
        else
        {
            newData.erase(prev(newData.end()));
        }
        newData += '\n';
    }

    if (!nameFound)
    {
        newData.erase(remove(newData.begin(), newData.end(), ' '), newData.end());
        newData += data;
    }

//    remove all spaces
    newData.erase(remove(newData.begin(), newData.end(), ' '), newData.end());

//    the file was initially  opened in read mode
//    we should close it and open it again in write mode
    csvData.close();
    csvData.open("assets/scores.csv");

    csvData << newData;
    csvData.close();
}

void updateData(string n1,string n2, int lvl , int sec )
{
    string name1 , name2;
//    soting the names
    if (n1 > n2) {name1 = n2 ; name2 = n1;}
    else {name1 = n1 ; name2 = n2;}

//    saving the record as a csv format
    string data ;
    data += name1;data += '-';
    data += name2;data += ',';
    data += to_string(lvl);
    data += '-';
    data += to_string(sec);

    writeData(data);
}

map<pair<string,string> , vector<int>> currentRecords;
void initializeCurrentRecords()
{
    fstream csvData;
    string temp;
    csvData.open("assets/scores.csv");
    pair<string,string> names;
    while (getline(csvData,temp))
    {
        if (temp != "")
        {
            vector<int> time(20);
            vector<string> record;
            vector<string>names2;
            split_to_string(record,temp,',');
            split_to_string(names2,record[0],'-');
            names2[0].erase(remove(names2[0].begin(), names2[0].end(), ' '), names2[0].end());
            names2[1].erase(remove(names2[1].begin(), names2[1].end(), ' '), names2[1].end());
            names.first = names2[0];
            names.second = names2[1];
            for (int i = 1 ; i < record.size() ; i++)
            {
                vector<string> levelAndTime;
                split_to_string(levelAndTime,record[i],'-');
                time[i-1] = str_to_int(levelAndTime[1]);
            }
            currentRecords[names] = time;
        }
    }
    csvData.close();
}

// Levels map and current level number
int level = 0;
String levelsMap [5][9] =
        {
                // Level 1
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
                // Level 2
                {
                        "                ",
                        "                ",
                        "LMMR            ",
                        "     M          ",
                        "       M        ",
                        "         M      ",
                        "           M    ",
                        "             M  ",
                        "                ",
                },
        };
//Pools Textures
Texture waterLeftText, waterMidText, waterRightText, lavaLeftText, lavaMidText, lavaRightText, acidLeftText, acidMidText, acidRightText;
Texture smallLavaText, smallAcidText, smallWaterText;
//Drawing platforms
Color color(0, 0, 0, 0);
vector<pair<RectangleShape, int> > platformObjects;
void fillPlatformObjects()
{
    //Registering pools as platforms
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            //Fire -> 1
            if (levelsMap[level][i][j] == 'f' || levelsMap[level][i][j] == 'i' || levelsMap[level][i][j] == 'r' || levelsMap[level][i][j] == 'F')
            {
                RectangleShape obj({ 80,40 });
                float posX = 40 + (80 * j), posY = 40 + (80 * i);
                obj.setPosition({ posX, posY });

                if (levelsMap[level][i][j] == 'f') { obj.setTexture(&lavaLeftText); }
                if (levelsMap[level][i][j] == 'i') { obj.setTexture(&lavaMidText); }
                if (levelsMap[level][i][j] == 'r') { obj.setTexture(&lavaRightText); }
                if (levelsMap[level][i][j] == 'F') { obj.setTexture(&smallLavaText); }
                platformObjects.push_back({ obj, 1 });
            }
            //Water -> 2
            if (levelsMap[level][i][j] == 'w' || levelsMap[level][i][j] == 'a' || levelsMap[level][i][j] == 't' || levelsMap[level][i][j] == 'W')
            {
                RectangleShape obj({ 80,40 });
                float posX = 40 + (80 * j), posY = 40 + (80 * i);
                obj.setPosition({ posX, posY });

                if (levelsMap[level][i][j] == 'w') { obj.setTexture(&waterLeftText); }
                if (levelsMap[level][i][j] == 'a') { obj.setTexture(&waterMidText); }
                if (levelsMap[level][i][j] == 't') { obj.setTexture(&waterRightText); }
                if (levelsMap[level][i][j] == 'W') { obj.setTexture(&smallWaterText); }

                platformObjects.push_back({ obj,2 });
            }
            //Mud -> 3
            if (levelsMap[level][i][j] == 'm' || levelsMap[level][i][j] == 'u' || levelsMap[level][i][j] == 'd' || levelsMap[level][i][j] == 'A')
            {
                RectangleShape obj({ 80,40 });
                float posX = 40 + (80 * j), posY = 40 + (80 * i);
                obj.setPosition({ posX, posY });

                if (levelsMap[level][i][j] == 'm') { obj.setTexture(&acidLeftText); }
                if (levelsMap[level][i][j] == 'u') { obj.setTexture(&acidMidText); }
                if (levelsMap[level][i][j] == 'd') { obj.setTexture(&acidRightText); }
                if (levelsMap[level][i][j] == 'A') { obj.setTexture(&smallAcidText); }

                platformObjects.push_back({ obj, 3 });
            }
        }
    }
    // Creating Objects for platforms
    int streak = 0;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            if (levelsMap[level][i][j] == 'L' || levelsMap[level][i][j] == 'M' || levelsMap[level][i][j] == 'R')
            {
                streak++;
            }
            else
            {
                if (streak)
                {
                    float start = (j - streak) * 80 + 40, end = start + (80 * streak);
                    RectangleShape obj({ end - start - 5, 40 });
                    obj.setPosition({ start, (float)(40 + 80 * i) });
                    obj.setFillColor(color);
                    platformObjects.push_back({ obj, 0 });
                    streak = 0;
                }
            }
        }
        if (streak)
        {
            float start = (15 - streak) * 80 + 40 + 80, end = start + (80 * streak);
            RectangleShape obj({ end - start, 40 });
            obj.setPosition({ start, (float)(40 + 80 * i) });
            obj.setFillColor(color);
            platformObjects.push_back({ obj, 0 });
            streak = 0;
        }
    }
    
}

int curPlatformObjectLevel = 100;

//  Declaring fireBoy and waterGirl sprites and textures
int jumpFactor = 42;
float gravity = 6.5;
Texture fireBoyTexture, waterGirlTexture;

int deathCounter = 0;
//Player struct
struct Player
{
    int jumpCnt = jumpFactor, ready = 1, groundCheck = 1;
    Sprite playerSprite;
    //character death
    // Declaring variable to store local bounds
    FloatRect bounds;
    // Declaring variables to store character's x and y coordinates
    float dx, dy;
    //Declaring type (1: fire, 2: water)
    int type;
    //Declaring state (dead or alive)
    bool isDead = 0;
    // Declaring waterGirl or fireBoy sprite for the first time and taking a texture as a parameter
    //Constructor
    Player(Texture& image, int element)
    {
        playerSprite.setTexture(image);
        playerSprite.setPosition({ 41.f, 599.f });

        type = element;

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
            playerSprite.setPosition({ 40, dy });

    }
    void Restart()
    {
        playerSprite.setPosition({ 41.f, 599.f });
        isDead = 0;
    }
    void move(pair < float, float> coordinates)
    {
        playerSprite.move({ coordinates.first,coordinates.second });
    }
    void die()
    {
        isDead = 1;
        playerSprite.setPosition(2000, 2000);
    }
};


int main()
{
    RenderWindow window(VideoMode(1280, 720), "Fireboy and Watergirl", Style::Titlebar | Style::Close);
    window.setFramerateLimit(60);

    initializeCurrentRecords();

    // Declaring characters
    fireBoyTexture.loadFromFile(m + "assets/graphics/fireBoy.png");
    waterGirlTexture.loadFromFile(m + "assets/graphics/waterGirl.png");
    Player fireBoy(fireBoyTexture,1), waterGirl(waterGirlTexture,2);
    
    //Pools Textures
    waterLeftText.loadFromFile(m + "assets/graphics/waterLeft.png");
    waterMidText.loadFromFile(m + "assets/graphics/waterMid.png");
    waterRightText.loadFromFile(m + "assets/graphics/waterRight.png");
    lavaLeftText.loadFromFile(m + "assets/graphics/lavaLeft.png");
    lavaMidText.loadFromFile(m + "assets/graphics/lavaMid.png");
    lavaRightText.loadFromFile(m + "assets/graphics/lavaRight.png");
    acidLeftText.loadFromFile(m + "assets/graphics/acidLeft.png");
    acidMidText.loadFromFile(m + "assets/graphics/acidMid.png");
    acidRightText.loadFromFile(m + "assets/graphics/acidRight.png");
    smallWaterText.loadFromFile(m + "assets/graphics/smallWater.png");
    smallAcidText.loadFromFile(m + "assets/graphics/smallAcid.png");
    smallLavaText.loadFromFile(m + "assets/graphics/smallLava.png");
    
    
    
    // Ground
    RectangleShape ground({ 1280, 1 });
    ground.setFillColor(color);
    ground.setPosition({ 0, 680 });

    const int H = 9, W = 16;
    // Background
    Texture textureBackground;
    textureBackground.loadFromFile(m + "assets/graphics/backGroundBrick.png");

    RectangleShape spriteBackground(Vector2f(80, 40));
    spriteBackground.setTexture(&textureBackground);

    // Asking for players' names
    string player1Name,player2Name;
    Text player1Text,player2Text;

    // Borders
    Texture textureSideBorder, textureBottomBorder, textureTopBorder;
    textureTopBorder.loadFromFile(m + "assets/graphics/topBorder.png");
    textureSideBorder.loadFromFile(m + "assets/graphics/sideBorder.png");
    textureBottomBorder.loadFromFile(m + "assets/graphics/bottomBorder.png");

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
    textureStoneMid.loadFromFile(m + "assets/graphics/stoneMid.png");
    RectangleShape spriteStoneMid(Vector2f(80.f, 40.f));
    spriteStoneMid.setTexture(&textureStoneMid);

    Texture textureStoneLeft;
    textureStoneLeft.loadFromFile(m + "assets/graphics/stoneLeft.png");
    RectangleShape spriteStoneLeft(Vector2f(80.f, 40.f));
    spriteStoneLeft.setTexture(&textureStoneLeft);

    Texture textureStoneRight;
    textureStoneRight.loadFromFile(m + "assets/graphics/stoneRight.png");
    RectangleShape spriteStoneRight(Vector2f(80.f, 40.f));
    spriteStoneRight.setTexture(&textureStoneRight);

    // Title
    Font fontTitle;
    fontTitle.loadFromFile(m + "assets/fonts/KOMIKAP_.ttf");

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

    //Enter your name guide
    Text textEnterYourName;
    textEnterYourName.setFont(fontTitle);

    textEnterYourName.setFillColor(Color::White);

    textEnterYourName.setCharacterSize(50);
    textEnterYourName.setString("Enter player 1 name:");
    textRect = textEnterYourName.getLocalBounds();
    textEnterYourName.setOrigin(textRect.left +
                                textRect.width / 2.0f,
                                textRect.top +
                                textRect.height / 2.0f);
    textEnterYourName.setPosition(640,230);

    // Player 1 name
    player1Text.setFont(fontTitle);

    player1Text.setFillColor(Color::White);
    textRect = player1Text.getLocalBounds();
    player1Text.setOrigin(textRect.left +
                          textRect.width / 2.0f,
                          textRect.top +
                          textRect.height / 2.0f);

    player1Text.setPosition(640,350);
    player1Text.setCharacterSize(40);

    // Player 2 name
    player2Text.setFont(fontTitle);
    player2Text.setFillColor(Color::White);
    textRect = player2Text.getLocalBounds();
    player2Text.setPosition(640,450);
    player2Text.setOrigin(textRect.left +
                          textRect.width / 2.0f,
                          textRect.top +
                          textRect.height / 2.0f);

    player2Text.setCharacterSize(40);

    // Players name input boxes
    RectangleShape enterYourNameRectangle;
    enterYourNameRectangle.setSize(Vector2f(910,45));

    Color color2 (255,255,255,0);
    enterYourNameRectangle.setFillColor(color2);
    enterYourNameRectangle.setOutlineThickness(5);
    enterYourNameRectangle.setOutlineColor(Color::White);
    textRect = enterYourNameRectangle.getLocalBounds();
    enterYourNameRectangle.setOrigin(textRect.left +
                                     textRect.width / 2.0f,
                                     textRect.top +
                                     textRect.height / 2.0f);
    enterYourNameRectangle.setPosition(640, 350);

    RectangleShape enterYourNameRectangle2 = enterYourNameRectangle;
    enterYourNameRectangle2.setPosition(640, 450);

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
    texturePauseBackground.loadFromFile(m + "assets/graphics/pauseBackground.png");

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

    // Game over
    Text textGameOver = textPaused;
    textGameOver.setString("Game over");
    textRect = textGameOver.getLocalBounds();
    textGameOver.setOrigin(textRect.left +
                         textRect.width / 2.0f,
                         textRect.top +
                         textRect.height / 2.0f);
    textGameOver.setPosition(640, 100);

    // Start
    Text textStart;
    textStart.setFont(fontTitle);
    textStart.setCharacterSize(50);
    textStart.setFillColor(Color::White);
    textStart.setString("Start");

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

    textRect = textRetryLevel.getLocalBounds();
    textRetryLevel.setOrigin(textRect.left +
                             textRect.width / 2.0f,
                             textRect.top +
                             textRect.height / 2.0f);
    textRetryLevel.setPosition(640, 400);

    // Continue
    Text textContinue;
    textContinue.setFont(fontTitle);
    textContinue.setCharacterSize(50);
    textContinue.setFillColor(Color::White);
    textContinue.setString("Continue");

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
    textContinueIntro.setString("Continue");

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

    // Level 1 (Test)
    Text textLevel1;
    textLevel1.setFont(fontTitle);
    textLevel1.setString("Level 1 (For testing)");
    textLevel1.setCharacterSize(70);
    textLevel1.setFillColor(Color::White);

    textRect = textLevel1.getLocalBounds();
    textLevel1.setOrigin(textRect.left +
                         textRect.width / 2.0f,
                         textRect.top +
                         textRect.height / 2.0f);
    textLevel1.setPosition(640, 300);

    // Level 2 (Test)
    Text textLevel2 = textLevel1;
    textLevel2.setString("Level 2 (For testing)");
    textLevel2.setPosition(640, 450);

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
    textureRedArrow.loadFromFile(m + "assets/graphics/redArrow.png");
    textureWhiteArrow.loadFromFile(m + "assets/graphics/whiteArrow.png");

    RectangleShape arrow;
    arrow.setSize(Vector2f(150,80));
    arrow.setPosition(30,40);
    arrow.setTexture(&textureWhiteArrow);

    // Door
    Texture textureDoor;
    textureDoor.loadFromFile(m + "assets/graphics/door.png");

    Sprite spriteDoor;
    spriteDoor.setTexture(textureDoor);

    // Sound effects
    SoundBuffer bufferFireboyJump, bufferWatergirlJump, bufferLevelComplete, bufferButtonHover, bufferPlayerDeath;
    bufferFireboyJump.loadFromFile(m + "assets/audio/fireboyJump.ogg");
    bufferButtonHover.loadFromFile(m + "assets/audio/buttonHover.ogg");
    bufferWatergirlJump.loadFromFile(m + "assets/audio/watergirlJump.ogg");
    bufferLevelComplete.loadFromFile(m + "assets/audio/levelComplete.ogg");
    bufferPlayerDeath.loadFromFile(m + "assets/audio/death.ogg");

    Sound soundButtonHover(bufferButtonHover);
    Sound soundLevelComplete(bufferLevelComplete);
    Sound soundFireboyJump(bufferFireboyJump), soundWatergirlJump(bufferWatergirlJump);
    Sound soundPlayerDeath(bufferPlayerDeath);


    // Music
    Music musicIntro, musicLevel;
    musicIntro.openFromFile(m + "assets/audio/intro.ogg");
    musicLevel.openFromFile(m + "assets/audio/level.ogg");
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
    bool player1Input = false;
    bool player2Input = false;
    bool bothPlayers = false;
    bool hoverExit = false;
    bool hoverStart = false;
    bool hoverArrow = false;
    bool hoverRetry = false;
    bool hoverContinue = false;
    bool hoverLevel1 = false;
    bool hoverLevel2 = false;
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
    bool enterYourNameFillColorInc = false;
    bool levelInquire = false;
    bool canType = true;

    int continueFillColor = 255;
    int enterYourNameFillColor = 255;

    Clock clock;

    // Main game loop
    while (window.isOpen())
    {
        // Check continue fill color increasing
        if (!continueFillColor) continueFillColorInc = true;
        else if (continueFillColor == 255) continueFillColorInc = false;

        // Check enter names fill color increasing
        if (!enterYourNameFillColor) enterYourNameFillColorInc = true;
        else if (enterYourNameFillColor == 255) enterYourNameFillColorInc = false;

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

        //Resistance
        for (auto i : platformObjects)
        {
            waterGirl.Inquire();
            //Y-axis
            if (waterGirl.bounds.intersects(i.first.getGlobalBounds()))
            {
                waterGirl.jumpCnt = jumpFactor + 1;
                if (waterGirl.dy < i.first.getPosition().y)
                {
                    pushedWaterGirl = false;
                    waterGirl.move({ 0, -gravity });
                    waterGirl.groundCheck = 1;
                    if ((i.second == 1 || i.second == 3) && !waterGirl.isDead) {
                        waterGirl.die();
                        soundPlayerDeath.play();
                    }
                }
            }
            fireBoy.Inquire();
            if (fireBoy.bounds.intersects(i.first.getGlobalBounds()))
            {
                fireBoy.jumpCnt = jumpFactor + 1;
                if (fireBoy.dy < i.first.getPosition().y)
                {
                    pushedFireBoy = false;
                    fireBoy.move({ 0, -gravity });
                    fireBoy.groundCheck = 1;
                    if ((i.second == 2 || i.second == 3) && !fireBoy.isDead) {
                        fireBoy.die();
                        soundPlayerDeath.play();
                    }
                }
            }

            //X-axis
            waterGirl.Inquire();
            if (waterGirl.bounds.intersects(i.first.getGlobalBounds()) && waterGirl.dy + 80 - safe >= i.first.getPosition().y && waterGirl.dx + 80 - safe >= i.first.getPosition().x)
            {
                pushedWaterGirl = true;
                waterGirl.move({ pixelsPerIteration, 0 });
            }
            waterGirl.Inquire();
            if (waterGirl.bounds.intersects(i.first.getGlobalBounds()) && waterGirl.dy + 80 - safe >= i.first.getPosition().y && waterGirl.dx + safe <= i.first.getPosition().x + i.first.getGlobalBounds().width)
            {
                pushedWaterGirl = true;
                waterGirl.move({ -pixelsPerIteration, 0 });
            }
            fireBoy.Inquire();
            if (fireBoy.bounds.intersects(i.first.getGlobalBounds()) && fireBoy.dy + 80 - safe >= i.first.getPosition().y && fireBoy.dx + 80 - safe >= i.first.getPosition().x)
            {
                pushedFireBoy = true;
                fireBoy.move({ pixelsPerIteration, 0 });
            }
            if (fireBoy.bounds.intersects(i.first.getGlobalBounds()) && fireBoy.dy + 80 - safe >= i.first.getPosition().y && fireBoy.dx + safe <= i.first.getPosition().x + i.first.getGlobalBounds().width)
            {
                pushedFireBoy = true;
                fireBoy.move({ -pixelsPerIteration, 0 });
            }
        }

        waterGirl.move({ 0, gravity });
        fireBoy.move({ 0, gravity });

        if (Keyboard::isKeyPressed(Keyboard::Key::D) && !paused && gameStarted)
        {
            if (!pushedWaterGirl) waterGirl.move({  1.825*pixelsPerIteration , 0});
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::A) && !paused && gameStarted)
        {
            if (!pushedWaterGirl) waterGirl.move({-1.825*pixelsPerIteration , 0});
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::Right) && !paused && gameStarted)
        {
            if (!pushedFireBoy && fireBoy.jumpCnt >= jumpFactor) fireBoy.move({ pixelsPerIteration , 0 });
            else if(!pushedFireBoy)fireBoy.move({ 1.825*pixelsPerIteration , 0 });
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::Left) && !paused && gameStarted)
        {
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

        if (gameStarted && !levelInquire)
        {
            if(musicMute)
                musicLevel.stop();

            // Render door
            window.draw(spriteDoor);

            if (level != curPlatformObjectLevel)
            {
                fireBoy.Restart(), waterGirl.Restart();
                platformObjects.clear();
                platformObjects.push_back({ground,0});
                fillPlatformObjects();
                curPlatformObjectLevel = level;
            }

            // Render level
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

            // Check if fireboy and Watergirl is still inside the drawn borders
            fireBoy.Inquire();
            waterGirl.Inquire();
            
            
            //Render pools
            for (auto i : platformObjects)
            {
                window.draw(i.first);
            }
            // Render border
            for (int i = 0; i < 4; i++) window.draw(borders[i]);

            // Render characters
            window.draw(fireBoy.playerSprite);
            window.draw(waterGirl.playerSprite);

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
                    updateData(player1Name, player2Name, level, seconds + minutes * 60);
                    initializeCurrentRecords();
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
        // Player 1 Name
        if(!gameStarted && !paused && !settingsMenu && started && !bothPlayers && player1Input && !player2Input && !levelInquire)
        {
            window.draw(enterYourNameRectangle);
            window.draw(enterYourNameRectangle2);
            if(event.type == sf::Event::TextEntered && event.text.unicode == 8 && !player1Name.empty() && canType)
            {
                canType = false;
                player1Name.pop_back();
                player1Text.setString(player1Name);
                window.draw(player1Text);
                continue;
            }
            else if(player1Name.size() >= 30)
            { //
            }
            else if(event.type == sf::Event::TextEntered && event.text.unicode <= 128 && event.text.unicode != 8 && !Keyboard::isKeyPressed(Keyboard::Key::Return) && canType)
            {
                canType = false;
                player1Name += tolower(event.text.unicode);
                player1Text.setString(player1Name);

            }
            // Player has entered player 1 name
            if(Keyboard::isKeyPressed(Keyboard::Key::Return) && !player1Name.empty())
            {
                player1Input = false;
                player2Input = true;
            }
            textRect = player1Text.getLocalBounds();
            player1Text.setOrigin(textRect.left +
                                  textRect.width / 2.0f,
                                  textRect.top +
                                  textRect.height / 2.0f);
            player1Text.setPosition(640,350);
            window.draw(textTitle);
            window.draw(player1Text);
            Color colorEnterYourName(255, 255, 255, enterYourNameFillColor -= ((enterYourNameFillColorInc) ? -5 : 5));
            textEnterYourName.setFillColor(colorEnterYourName);
            window.draw(textEnterYourName);
        }

            // Player 2 name
        else if(!gameStarted && !paused && !settingsMenu && started && !bothPlayers && !player1Input && player2Input && !levelInquire)
        {
            window.draw(enterYourNameRectangle);
            window.draw(enterYourNameRectangle2);
            if(event.type == sf::Event::TextEntered && event.text.unicode == 8 && !player2Name.empty() && canType)
            {
                canType = false;
                player2Name.pop_back();
                player2Text.setString(player2Name);
                window.draw(player2Text);
                continue;
            }
            else if(player2Name.size() >= 30)
            { //
            }
            else if(event.type == sf::Event::TextEntered && event.text.unicode <= 128 && event.text.unicode != 8 && !Keyboard::isKeyPressed(Keyboard::Key::Return) && canType)
            {
                canType = false;
                player2Name += tolower(event.text.unicode);
                player2Text.setString(player2Name);

            }
            // Player has entered player 2 name
            if(Keyboard::isKeyPressed(Keyboard::Key::Return) && !player2Name.empty())
            {
                player1Input = true, player2Input = true;
                bothPlayers = true;
            }

            window.draw(textTitle);
            window.draw(player1Text);
            window.draw(player2Text);
            Color colorEnterYourName(255, 255, 255, enterYourNameFillColor -= ((enterYourNameFillColor) ? -5 : 5));
            textEnterYourName.setFillColor(colorEnterYourName);
            textEnterYourName.setString("Enter player 2 name:");
            textRect = player2Text.getLocalBounds();
            player2Text.setOrigin(textRect.left +
                                  textRect.width / 2.0f,
                                  textRect.top +
                                  textRect.height / 2.0f);
            player2Text.setPosition(640,450);
            window.draw(textEnterYourName);
        }
        if (!gameStarted && !paused && !settingsMenu && started && bothPlayers && !levelInquire)
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
                    levelInquire = true;
                    chron.reset(), chron.resume();
                }
            }
            else {
                hoverStart = false;
                textStart.setFillColor(Color::White);
            }
            window.draw(textStart);
        }

        // Level inquire
        if (levelInquire && started && !gameStarted && !paused && !settingsMenu && bothPlayers)
        {
            string currentPlayer1 = min({player1Name, player2Name});
            string currentPlayer2 = max({player1Name, player2Name});

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
                if (Mouse::isButtonPressed(Mouse::Left))
                {
                    level = 0;
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
            if (currentRecords[{currentPlayer1, currentPlayer2}].size() > 0 && currentRecords[{currentPlayer1, currentPlayer2}][0] && !gameStarted && mouse_xAxis >= 237 && mouse_xAxis <= 1043 && mouse_yAxis >= 418.5 && mouse_yAxis <= 481.5)
            {
                if (!hoverLevel2)
                {
                    soundButtonHover.play();
                    hoverLevel2 = true;
                }
                textLevel2.setFillColor(Color::Green);
                if (Mouse::isButtonPressed(Mouse::Left))
                {
                    level = 1;
                    spriteDoor.setPosition(120, 95);
                    gameStarted = true, levelInquire = false;
                    musicIntro.stop();
                    musicLevel.play();
                    chron.reset(), chron.resume();
                }
            }
            else {
                hoverLevel2 = false;
                textLevel2.setFillColor(Color::White);
            }
        }

        if (!gameStarted || paused || settingsMenu)
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
        }

        if ((paused || !gameStarted) && !settingsMenu && started && bothPlayers && !levelInquire)
        {

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
        if (paused && !settingsMenu && started && !levelInquire)
        {
            // Render text paused
            if (!fireBoy.isDead && !waterGirl.isDead) window.draw(textPaused);

            // Render text game over
            if (fireBoy.isDead || waterGirl.isDead) window.draw(textGameOver);

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
            if (mouse_xAxis >= 476.5 && mouse_xAxis <= 803.5 && mouse_yAxis >= 379 && mouse_yAxis <= 421)
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
        if (settingsMenu && started && !levelInquire)
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
                    started = true, player1Input = true;
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






