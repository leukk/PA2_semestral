#pragma once
#include "../singleton-managers/GameManager.h"
#include "../structs/Level.h"
#include "../structs/Item.h"
#include "GameConstants.h"
#include "PlayerData.h"
#include <string>
#include <ncurses.h>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>

using std::min;
using std::string, std::stoi, std::to_string;
using std::map, std::vector, std::distance;
using std::ifstream, std::ofstream, std::istringstream, std::ostringstream;
using std::exception, std::logic_error, std::invalid_argument;

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

    void SetPlayerDataFilePath();
    void UnsetPlayerDataFilePath();
    void LoadPlayerData();
    void SavePlayerData();
    void SetDefaultPlayerStats();
    const string& PlayerDataPath();

    const vector<Level>& ConfigLevels();
    const vector<Item>& ConfigItems();

    PlayerData playerData;
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

    string m_playerDataPath;

    // Preprocessed data
    vector<Level> m_levels;
    vector<Item> m_items;
};
