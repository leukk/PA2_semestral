#pragma once
#include "../managers/GameManager.h"
#include "GameConstants.h"
#include "Level.h"
#include "Item.h"
#include <string>
#include <ncurses.h>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>

using std::min;
using std::string, std::stoi;
using std::map, std::vector, std::distance;
using std::ifstream, std::ofstream, std::istringstream, std::ostringstream;
using std::exception, std::logic_error, std::invalid_argument;

#define SHARED_PARAMETERS -1;

class DataLoader {
public:
    DataLoader();
    DataLoader(const DataLoader& other) = default;
    ~DataLoader() = default;

    static string GetInputString(const string& prompt);

    bool LoadMainConfig(char * argConfig);
    [[nodiscard]] size_t ConfigSceneCount() const;
    [[nodiscard]] size_t ConfigObjectCount(int sceneIndex) const;
    [[nodiscard]] string ConfigGetParam(int sceneIndex, int objectIndex, const string& param) const;
    [[nodiscard]] int ConfigGetNumParam(int sceneIndex, int objectIndex, const string& param) const;

    void SetPlayerDataFile();
    void LoadPlayerData();
    void SavePlayerData();
    void SetDefaultPlayerStats();

    void PlayerDataSet(const string& key, const string& value);
    void PlayerDataSetNum(const string& key, int value);
    void PlayerDataSetNums(const string& key, const vector<int>& values);
    string PlayerDataGet(const string& key);
    int PlayerDataGetNum(const string& key);
    vector<int> PlayerDataGetNums(const string& key);
    const string& PlayerDataPath();

    const vector<Level>& ConfigLevels();
    const vector<Item>& ConfigItems();

private:
    static string m_GetMainConfigPath(char * argConfig);
    static string m_GetConfigString(const string &configPath);
    void m_ProcessConfigString();
    void m_ProcessParameters(const string &prefix);
    void m_ProcessItems();
    void m_ProcessLevels();

private:
    // Config variables
    string m_configString;
    map<string, string> m_configData;
    vector<int> m_sceneObjectCounts;

    // Player data variables
    string m_playerDataPath;
    map<string, string> m_playerData;

    // Preprocessed data
    vector<Level> m_levels;
    vector<Item> m_items;
};
