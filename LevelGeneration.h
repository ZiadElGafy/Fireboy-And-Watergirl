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
#include "Visuals.h"
using namespace std;
using namespace sf;
using namespace sftools;


// Theme
bool sand = false, stone = true;

// Enemies Vector
vector <pair<RectangleShape, pair<float, float>>> enemies;

// Current level
int level = 0;
// Levels map
String levelsMap[11][9] =
        {
                /*
                    MAP KEY
                    G: gate button
                    B: bridge button
                    M: Mid block
                    L: left block
                    R: right block
                    W: small water
                    F: small lava
                    f: left lava
                    i: mid lava
                    r: right lava
                    w:left water
                    a: mid water
                    t: right water

                */
                // Level 1 (Hazem)
                {
                        "                ",
                        "                ",
                        "         LMMMMMM",
                        "                ",
                        "GR       LMMGMMM",
                        "    LMBR        ",
                        "           LBR  ",
                        "    LfirR       ",
                        "                ",
                },
                // Level 2 (Jana)
                {
                        "                ",
                        "                ",
                        "          LBMMMR",
                        "       M        ",
                        "LBMR        LMMR",
                        "      LMMR      ",
                        " fir        wat ",
                        "      LMMR      ",
                        "                ",
                },
                // Level 3 (Shahd)
                {
                        "                ",
                        "                ",
                        "         LMMMMM ",
                        "MMMMMMR         ",
                        "       M        ",
                        "          LFR   ",
                        "      LMR       ",
                        " LWR            ",
                        "                ",
                },
                // Level 4 (Ziad)
                {
                        "                ",
                        "                ",
                        "MMMMMMMMMMMR    ",
                        "              MM",
                        "   LMMMMMMMMMMMM",
                        "M               ",
                        "MMMMMBMMMMR  M  ",
                        "            MM  ",
                        "              G ",
                },
                // Level 5 (Beevo)
                {
                        "                ",
                        "                ",
                        "LMBR    BMG     ",
                        "                ",
                        "   GMMMMMBMMMmu ",
                        "                ",
                        "                ",
                        " LMMMMMMfiiirMB ",
                        "                ",
                },
                // Level 6 (Youssif)
                {
                        "                ",
                        "                ",
                        "                ",
                        "LG              ",
                        "    L    R      ",
                        "BMMMfiiiirMR    ",
                        "              M ",
                        "   G  B         ",
                        "                ",
                },
                // Level 7 (Maram)
               {
                       "                ",
                       "                ",
                       "LMR         LMGR",
                       "                ",
                       "LBfirR    BMMMMR",
                       "                ",
                       "LMMMMR     LMMMR",
                       "                ",
                       "                ",
               },
                // Level 8 (Ziad)
                {
                        "                ",
                        "                ",
                        " firR     GWR LR",
                        " M     M   M    ",
                        " M  M      M    ",
                        " M              ",
                        " MMMMMMMR  M    ",
                        " M         Mmud ",
                        "B               ",
                },
                // Level 9 (Maram)
                {
                    "                ",
                    "                ",
                    "LMGMMR   LMMMWMG",
                    "                ",
                    "                ",
                    "                ",
                    "LMMFBR     LMGMR",
                    "                ",
                    "              B ",
                },
                // Level 10 (Beevo)
                {
                        "                ",
                        "                ",
                        " LFMMFMMMMMMBR  ",
                        "                ",
                        "                ",
                        " LMMWMMWMMAMMGM ",
                        "                ",
                        "M M M M M M LMR ",
                        "muuuuuuuuuuuuud ",
                },        
        };


/*
    Map Key
    T: gate top
    M: gate mid
    B: gate bottom
    L: bridge start
    W: bridge mid
    E: enemy
    D: door
    g: red gem
    G: blue gem
    O: box
*/
String objectsMap[11][36] =
        {
                // Level 1 (Hazem)
                {

                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                      T                D        ",
                        "                                      M                         ",
                        "                                      M      g                  ",
                        "                                      M                         ",
                        "                                      M                         ",
                        "                                      M                         ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "    G                                                           ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "LWWWWWWWW                                                       ",
                        "                         g                                      ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                "
                },
                // Level 2 (Jana)
                {
                        "                                                                ",
                        "                                                                ",
                        "                                                       D        ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                LWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "         g                                           G          ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                "
                },
                // Level 3 (Shahd)
                {
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                      D         ",
                        "                                                                ",
                        "                                                                ",
                        "                                     E                          ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "   G   g  E                                                     ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                             g                  ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "         G                                                      ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                "
                },
                // Level 4 (Ziad)
                {

                        "        T                                                       ",
                        "        M                                                       ",
                        "  D     M                                                       ",
                        "        M                                                       ",
                        "        M                                                       ",
                        "        M      O                                                ",
                        "        M                                                       ",
                        "        M                                                       ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                        Q       ",
                        "                                                                ",
                        "                                                        Q       ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "Q                                                               ",
                        "                                                                ",
                        "Q                                           LWWWWWWWW           ",
                        "                                                                ",
                        "                                                    Q           ",
                        "                                                                ",
                        "                                                    Q           ",
                        "                                                                ",
                        "                                                Q   Q           ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                "
                },
                // Level 5 (Beevo)
                {
                        "                                                                ",
                        "                                                                ",
                        "    D                                                           ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                LWWWWWWWWWWWWWWWW                               ",
                        "                        G                                       ",
                        "                                           T                    ",
                        "                                           M                    ",
                        "                                           M                    ",
                        "                                        O  M                    ",
                        "                E                          M                    ",
                        "  g                                        B                    ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                         g                      ",
                        "LWWWW                                                           ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "              E                                                 ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                },
                // Level 6 (Youssif)
                {

                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "D                                                               ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "      T                                                         ",
                        "      M                                                         ",
                        "      M             LWWWWWWWWWWWWWWW                            ",
                        "      M                                      O                  ",
                        "      M                                                         ",
                        "      B                                                         ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                "
                },
                // Level 7 (Maram)
                {
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                 O              ",
                        "                                                                ",
                        "                                                                ",
                        "                                                   g            ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                    O                      O                    ",
                        "  g                                                             ",
                        "                                                                ",
                        "                        LWWWWWWWWWWWWWWW                        ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "             O                                                  ",
                        "                                                  E  G          ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                T      D        ",
                        "                                                M               ",
                        "                                                M               ",
                        "                               O                M               ",
                        "                   E                            M      g        ",
                        "                                                B               ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                },
                // Level 8 (Ziad)
                {

                        "                   T                                            ",
                        "        G          M                                            ",
                        "                   M                                            ",
                        "                   M                         g                  ",
                        "          O        M                                            ",
                        "                   M                                            ",
                        "                   M                                            ",
                        "                   M                                            ",
                        " g                                                              ",
                        "                                                                ",
                        "    Q                                       Q           D       ",
                        "                                                                ",
                        "    Q                                       Q                   ",
                        "                                                                ",
                        "    Q                                       Q                   ",
                        "                                                                ",
                        "    Q                                       Q                   ",
                        "                                                                ",
                        "    Q                                                           ",
                        "                                                  G             ",
                        "    Q                                                           ",
                        "        O                                                       ",
                        "    Q       E                                                   ",
                        "                                                                ",
                        "    Q                                           LWWWWWWWWWWWWWW ",
                        "                                                                ",
                        "    Q                                       Q                   ",
                        "                                                                ",
                        "    Q                                       Q                   ",
                        "                                   O                            ",
                        "    Q                                       Q   Q   Q   Q   Q   ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                "
                },
                // Level 9 (Maram)
                {

                        "                     T                                          ",
                        "                     M                                          ",
                        "                     M                                          ",
                        "                     M                                          ",
                        "       O             M                                          ",
                        "                     M       D             O                    ",
                        "                     M                                          ",
                        "                     B                                      g   ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                            G    g                              ",
                        "                                                                ",
                        "                                                                ",
                        "                        LWWWWWWWWWWWWW                          ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "         O                                    O                 ",
                        "                                                                ",
                        "      G                                            E   g        ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                            T                   ",
                        "                                            M                   ",
                        "                                            M                   ",
                        "                                            M       O           ",
                        "    G              E                        M                   ",
                        "                                            B                   ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                "
                },
                // Level 10 (Beevo)
                {

                        "                                 Q                     T        ",
                        "                                 Q                     M        ",
                        "         G                       Q                     M        ",
                        "                                 Q                     M        ",
                        "                                 Q                     M        ",
                        "                                 Q                     M        ",
                        "                                 Q   E                 M        ",
                        "                                                       M        ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                 g                                              ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "LWWWWWWWW                                                       ",
                        "                                                                ",
                        "                                                       D        ",
                        "                                                                ",
                        "     G       g       G       g       G       g                  ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                "
                },
        };

//Drawing platforms
vector<pair<pair<RectangleShape, int>, int> > platformObjects;
int buttonCnt = 10;

int gateCnt = 0, bridgeCnt = 0;
vector<pair<pair<RectangleShape, int>, int>> gatesObjects;
vector<pair<pair<RectangleShape, int>, int>> gemObjects;
vector<pair<Sprite, pair<int,int>>>pools;
vector<pair<Sprite, int>>fillings;
int buttonGateCnt = 0, buttonBridgeCnt = 0;
int gemCnt = 0;

// boxes
vector<Sprite> boxes;
vector<pair<float,float>> boxesPositions;


void fillPlatformObjects()
{
    // Registering pools as platforms
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            // Fire -> 1
            if (levelsMap[level][i][j] == 'f' || levelsMap[level][i][j] == 'i' || levelsMap[level][i][j] == 'r' || levelsMap[level][i][j] == 'F')
            {
                RectangleShape obj({80,40});
                float posX = 40 + (80 * j), posY = 40 + (80 * i);
                obj.setPosition({posX, posY});

                if (levelsMap[level][i][j] == 'f')
                {
                    spriteLavaLeft.setPosition({posX, posY});
                    pools.push_back({spriteLavaLeft,{1,0}});
                }
                if (levelsMap[level][i][j] == 'i')
                {
                    spriteLavaMid.setPosition({posX, posY});
                    pools.push_back({spriteLavaMid,{1,1}});
                }
                if (levelsMap[level][i][j] == 'r')
                {
                    spriteLavaRight.setPosition({posX, posY});
                    pools.push_back({spriteLavaRight,{1,2}});
                }
                if (levelsMap[level][i][j] == 'F')
                {
                    spriteSmallLava.setPosition({posX, posY});
                   pools.push_back({spriteSmallLava,{1,3}});
                }
                platformObjects.push_back({ {obj, 1},0});
            }
            // Water -> 2
            if (levelsMap[level][i][j] == 'w' || levelsMap[level][i][j] == 'a' || levelsMap[level][i][j] == 't' || levelsMap[level][i][j] == 'W')
            {
                RectangleShape obj({80,40});
                float posX = 40 + (80 * j), posY = 40 + (80 * i);
                obj.setPosition({posX, posY});

                if (levelsMap[level][i][j] == 'w')
                {
                    spriteWaterLeft.setPosition({posX, posY});
                    pools.push_back({spriteWaterLeft,{2,0}});
                }
                if (levelsMap[level][i][j] == 'a')
                {
                    spriteWaterMid.setPosition({posX, posY});
                    pools.push_back({spriteWaterMid,{2,1}});
                }
                if (levelsMap[level][i][j] == 't')
                {
                    spriteWaterRight.setPosition({posX, posY});
                    pools.push_back({spriteWaterRight,{2,2}});
                }
                if (levelsMap[level][i][j] == 'W')
                {
                    spriteSmallWater.setPosition({posX, posY});
                    pools.push_back({spriteSmallWater,{2,3}});
                }
                platformObjects.push_back({ {obj,2},0});
            }
            // Mud -> 3
            if (levelsMap[level][i][j] == 'm' || levelsMap[level][i][j] == 'u' || levelsMap[level][i][j] == 'd' || levelsMap[level][i][j] == 'A')
            {
                RectangleShape obj({80,40});
                float posX = 40 + (80 * j), posY = 40 + (80 * i);
                obj.setPosition({posX, posY});

                if (levelsMap[level][i][j] == 'm')
                {
                    spriteAcidLeft.setPosition({posX, posY});
                    pools.push_back({spriteAcidLeft,{3,0}});
                }
                if (levelsMap[level][i][j] == 'u')
                {
                    spriteAcidMid.setPosition({posX, posY});
                    pools.push_back({spriteAcidMid,{3,1}});
                }
                if (levelsMap[level][i][j] == 'd')
                {
                    spriteAcidRight.setPosition({posX, posY});
                    pools.push_back({spriteAcidRight,{3,2}});
                }
                if (levelsMap[level][i][j] == 'A')
                {
                    spriteSmallAcid.setPosition({posX, posY});
                    pools.push_back({spriteSmallAcid, {3,3}});
                }
                platformObjects.push_back({ {obj, 3},0});
            }
            //Button for Gate -> 4  Button for bridge -> 5
            if (levelsMap[level][i][j] == 'G' || levelsMap[level][i][j] == 'B')
            {
                RectangleShape obj;
                obj.setSize({80, 40});
                float posX = 40 + (80 * j), posY = 40 + (80 * i);
                obj.setPosition({posX, posY});
                if (levelsMap[level][i][j] == 'G')
                {
                    platformObjects.push_back({{obj, 4 },++buttonGateCnt});
                }
                else
                {
                    platformObjects.push_back({{obj, 5 },++buttonBridgeCnt});
                }
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
                    RectangleShape obj({end - start - 5, 40});
                    obj.setPosition({start, (float)(40 + 80 * i)});
                    obj.setFillColor(color);
                    platformObjects.push_back({{ obj, 0 },0});
                    streak = 0;
                }
            }
        }
        if (streak)
        {
            float start = (15 - streak) * 80 + 40 + 80, end = start + (80 * streak);
            RectangleShape obj({end - start - 5, 40});
            obj.setPosition({start, (float)(40 + 80 * i)});
            obj.setFillColor(color);
            platformObjects.push_back({{obj, 0 },0});
            streak = 0;
        }
    }
}

void fillGateObjects()
{
    for (int i = 0; i < 36; ++i)
    {
        for (int j = 0; j < 64; ++j)
        {
            RectangleShape obj({20,20});
            float posX = 40 + (20 * j), posY = 40 + (20 * i);
            obj.setPosition({posX, posY});

            if (objectsMap[level][i][j] == 'T')
            {
                ++gateCnt;
                obj.setTexture(&textureGateTop);
                gatesObjects.push_back({{obj, 0 },gateCnt});
            }
            else if (objectsMap[level][i][j] == 'M')
            {
                obj.setTexture(&textureGateMiddle);
                gatesObjects.push_back({{obj, 1},gateCnt});
            }
            else if (objectsMap[level][i][j] == 'B')
            {
                obj.setTexture(&textureGateBottom);
                gatesObjects.push_back({{obj, 2},gateCnt});
            }
            else if (objectsMap[level][i][j] == 'L')
            {
                ++bridgeCnt;
                obj.setTexture(&textureBridgeLeft);
                gatesObjects.push_back({{obj, 3},bridgeCnt});
            }
            else if (objectsMap[level][i][j] == 'W')
            {
                obj.setTexture(&textureBridgeMiddle);
                gatesObjects.push_back({{obj, 4 },bridgeCnt});
            }
            // Box -> 5
            else if(objectsMap[level][i][j] == 'O')
            {
                posX = 40 + (20 * j), posY = 40 + (20 * i);
                spriteBox.setPosition(posX, posY);
                
                boxes.push_back(spriteBox);
                boxesPositions.push_back({posX,posY});
            }
            // Door
            else if (objectsMap[level][i][j] == 'D')
            {
                spriteDoor.setPosition({posX, posY});
            }
            // Enemy
            
            if (objectsMap[level][i][j] == 'E')
            {
                RectangleShape enemyObj({ 40,40 });
                enemyObj.setTexture(&enemyText);
                enemyObj.setPosition({ posX,posY });
                enemies.push_back({ enemyObj,{posX,posY} });
            }
            if (objectsMap[level][i][j] == 'Q')
            {
                RectangleShape obj5({ 80, 40 });
                posX = 40 + (20 * j), posY = 40 + (20 * i);
                obj5.setPosition({ posX, posY });
                if (sand)
                {
                    Sprite temp;
                    temp.setPosition({posX, posY});
                    fillings.push_back({temp,1});
                    obj5.setTexture(&sandFillingText);
                }
                else if(stone)
                {
                    Sprite temp;
                    temp.setPosition({posX, posY});
                    fillings.push_back({temp,0});
                    obj5.setTexture(&stoneFillingText);
                }
                gatesObjects.push_back({ {obj5, 6},-1 });
            }
        }
    }
}

void boxesRestart()
{
    for(int i = 0;i < boxes.size();++i)
    {
        boxes[i].setPosition(boxesPositions[i].first, boxesPositions[i].second);
    }
}

void fillGemObjects()
{
    for (int i = 0; i < 36; ++i)
    {
        for (int j = 0; j < 64; ++j)
        {
            RectangleShape obj({40,40});
            float posX = 40 + (20 * j), posY = 40 + (20 * i);
            obj.setPosition({posX, posY});

            if (objectsMap[level][i][j] == 'G')
            {
                obj.setTexture(&textureBlueGem);
                gemObjects.push_back({{obj, 1}, ++gemCnt});
            }
            else if (objectsMap[level][i][j] == 'g')
            {
                obj.setTexture(&textureRedGem);
                gemObjects.push_back({{obj, 0}, ++gemCnt});
            }
        }
    }
}

// Current drawn level on the screen
int curPlatformObjectLevel = 100;

