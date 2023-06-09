#pragma once
#include "GameConstants.h"
#include <string>
#include <ncurses.h>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>

using std::min;
using std::string, std::stoi;
using std::map, std::vector, std::distance;
using std::ifstream, std::istringstream, std::ostringstream;
using std::exception, std::logic_error, std::invalid_argument;

#define SHARED_PARAMETERS -1;

class DataLoader {
public:
    DataLoader();
    DataLoader(const DataLoader& other) = default;
    ~DataLoader() = default;

    bool LoadMainConfig(WINDOW *interactionWin, char * argConfig);
    [[nodiscard]] size_t ConfigSceneCount() const;
    [[nodiscard]] size_t ConfigObjectCount(int sceneIndex) const;
    [[nodiscard]] string ConfigGetParam(int sceneIndex, int objectIndex, const string& param) const;
    [[nodiscard]] int ConfigGetNumParam(int sceneIndex, int objectIndex, const string& param) const;

    void LoadPlayerData(WINDOW * interactionWin);
    void PlayerDataSave(string key, string value);
    void PlayerDataLoad(string key, string value);

private:
    static string m_GetMainConfigPath(WINDOW * interactionWin, char * argConfig);
    static string m_GetConfigString(const string &configPath);
    void m_ProcessConfigString();
    void m_ProcessParameters(const string &prefix);


private:
    string m_configString;
    map<string, string> m_configData;
    vector<int> m_sceneObjectCounts;
};
