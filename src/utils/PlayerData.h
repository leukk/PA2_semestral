#pragma once
#include "GameConstants.h"
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using std::string, std::vector;
using std::ifstream, std::ofstream;
using std::istringstream, std::ostringstream;

struct PlayerData{
    PlayerData() = default;
    PlayerData(const PlayerData& other) = default;
    ~PlayerData() = default;

    void Write(ofstream &output);
    void Read(ifstream &input);

    vector<int> equippedItems{};
    vector<int> ownedItems{};
    int nextLevelIndex = 0;
    int role = 0;
    int coins = 0;
    int speed = 2;
    int lives = 3;
    int range = 10;

private:
    static void m_WriteNumVector(ofstream& output, vector<int>& vec);
    static void m_WriteNum(ofstream& output, int num);
    static void m_ReadNumVector(ifstream& input, vector<int>& vec);
    static void m_ReadNum(ifstream& input, int& num);
    static string m_GetLineValue(ifstream &input);
};


