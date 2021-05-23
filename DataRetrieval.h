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

string mHolder = "/Users/pluto/Desktop/Fireboy-And-Watergirl/";
string m = "";

// Declaring intro text
string introText = "";

// Loading intro text
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

void split_to_string(vector<string>& vec, string& str, char splitter)
{
    string one_word = " ";
    for (char c : str)
    {
        if (c == splitter) { vec.push_back(one_word); one_word = " "; }
        else { one_word += c; }
    }
    vec.push_back(one_word);
}

int char_to_int(char c)
{
    return (c - '0');
}

int str_to_int(string& str)
{
    if (str.length() == 1) { return char_to_int(str[0]); }
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
    split_to_string(newRecord, data, ',');

    bool found;
    bool levelExist;
    bool newRecordFound;
    bool nameFound = false;
    while (getline(csvData, temp))
    {
        found = false;
        vector<string> currRecord;
        split_to_string(currRecord, temp, ',');

        // Given that the pair of names is sorted so <a,b> is same as <b,a> because both of them will be <a,b>
        if (currRecord[0] == newRecord[0])
        {
            newData += currRecord[0];
            newData += ',';

            found = true;
            nameFound = true;
            newRecordFound = false;
            vector<string> tempNewRecord;
            split_to_string(tempNewRecord, newRecord[1], '-');
            for (int i = 1; i < currRecord.size(); i++)
            {
                levelExist = false;
                vector<string> tempCurrRecord;
                split_to_string(tempCurrRecord, currRecord[i], '-');

                // Given that the levels are sorted
                if (tempCurrRecord[0] == tempNewRecord[0])
                {
                    levelExist = true;
                    newRecordFound = true;
                    if (str_to_int(tempCurrRecord[1]) > str_to_int(tempNewRecord[1]))
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
            newData += temp;
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

    // Remove all spaces
    newData.erase(remove(newData.begin(), newData.end(), ' '), newData.end());

    // The file was initially  opened in read mode
    // We should close it and open it again in write mode
    csvData.close();
    csvData.open("assets/scores.csv");

    csvData << newData;
    csvData.close();
}

void updateData(string n1, string n2, int lvl, int sec)
{
    string name1, name2;
    // Sorting the names
    if (n1 > n2) { name1 = n2; name2 = n1; }
    else { name1 = n1; name2 = n2; }

    // Saving the record as a csv format
    string data;
    data += name1; data += '-';
    data += name2; data += ',';
    data += to_string(lvl);
    data += '-';
    data += to_string(sec);

    writeData(data);
}

vector<int> guestRecords(20, 0);
map<pair<string, string>, vector<int>> currentRecords;

void initializeCurrentRecords()
{
    fstream csvData;
    string temp;
    csvData.open("assets/scores.csv");
    pair<string, string> names;
    while (getline(csvData, temp))
    {
        if (temp != "")
        {
            vector<int> TIME(20);
            vector<string> record;
            vector<string>names2;
            split_to_string(record, temp, ',');
            split_to_string(names2, record[0], '-');
            names2[0].erase(remove(names2[0].begin(), names2[0].end(), ' '), names2[0].end());
            names2[1].erase(remove(names2[1].begin(), names2[1].end(), ' '), names2[1].end());
            names.first = names2[0];
            names.second = names2[1];
            for (int i = 1; i < record.size(); i++)
            {
                vector<string> levelAndTime;
                split_to_string(levelAndTime, record[i], '-');
                TIME[i - 1] = str_to_int(levelAndTime[1]);
            }
            currentRecords[names] = TIME;
        }
    }
    csvData.close();
}

vector<pair<int, pair<string, string>>> topTen;

void getTopTenOfLevel(int level)
{
    // Just to make sure the map is initialized
    initializeCurrentRecords();

    // Clearing the vector to avoid past data existence
    topTen.clear();

    map<pair<string, string>, vector<int>>::iterator it;
    for (it = currentRecords.begin(); it != currentRecords.end(); it++)
    {
        if (it->second[level - 1] != 0)
        {
            topTen.push_back({ it->second[level - 1],{it->first.first,it->first.second} });
        }
    }
    sort(topTen.begin(), topTen.end());

    // topTen may contains more or less than 10 records so take that into consideration
}
