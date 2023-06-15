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

/**
 * Source of all config / savable player data.
 * @warning needs to be initialized before use.
 */
class DataLoader {
public:
    DataLoader();
    DataLoader(const DataLoader& other) = default;
    ~DataLoader() = default;

    /**
     * Loads input string from user.
     *
     * Pauses game execution, enables blocking input and
     * asks user for user input via prompt.
     * Reads at most MAX_USER_INPUT_LENGTH characters.
     * @param prompt user input prompt
     * @return user input
     */
    static string GetInputString(const string& prompt);

    /**
     * Loads main game config.
     *
     * Loads config from file & parses its contents.
     * @param argConfig game config path supplied by arguments
     * @return config successfully loaded
     */
    bool LoadMainConfig(char * argConfig);

    /**
     * Number of scenes found in config.
     * @return number of scenes in config
     */
    [[nodiscard]] size_t ConfigSceneCount() const;

    /**
     * Number of objects found within one config scene.
     * @param sceneIndex index of scene to get object count from
     * @return number of objects
     */
    [[nodiscard]] size_t ConfigObjectCount(int sceneIndex) const;

    /**
     * Retrieves parameter from particular object from particular scene.
     *
     * Retrieves string parameter data from object at objectIndex from
     * scene at (sceneIndex) defined by parameter keyword.
     * For example (1,0,"--test") - retrieves 0th objects from 1st scene parameter
     * defined by keyword "--test"
     * @note use SHARED_INDEX for global data / data shared within one scene
     * @note returns empty string if parameter not found
     * @param sceneIndex objects scene index
     * @param objectIndex object index
     * @param param objects parameter keyword
     * @return value found
     */
    [[nodiscard]] string ConfigGetParam(int sceneIndex, int objectIndex, const string& param) const;

    /**
     * ConfigGetParam wrapper, attempts numeric conversion.
     *
     * Gets parameter data via ConfigGetParam() and converts it to integer.
     * @note returns 0 if parameter not found / found empty
     * @warning throws if parameter not numeric
     * @param sceneIndex objects scene index
     * @param objectIndex objects index
     * @param param objects parameter keyword
     * @return numeric value found
     */
    [[nodiscard]] int ConfigGetNumParam(int sceneIndex, int objectIndex, const string& param) const;

    /**
     * Clears & asks user for player data file path
     */
    void SetPlayerDataFilePath();

    /**
     * Clears player data file path
     */
    void UnsetPlayerDataFilePath();

    /**
     * Loads player data from file on current player data file path
     * @warning throws if filepath invalid
     */
    void LoadPlayerData();

    /**
     * Saves player data to file on current player data file path
     * @warning throws if filepath invalid
     */
    void SavePlayerData();

    /**
     * Sets playerData to default values.
     */
    void SetDefaultPlayerStats();

    /**
     * Current player data file path getter.
     * @return data file path
     */
    const string& PlayerDataPath();

    /**
     * Getter to vector of levels defined in config
     * @return const level vector
     */
    const vector<Level>& ConfigLevels();
    /**
     * Getter to vector of items defined in config
     * @return const items vector
     */
    const vector<Item>& ConfigItems();

    PlayerData playerData; /// currently loaded player data
private:
    /**
     * Attempts to first load config using argConfig - config supplied by program arguments.
     * If no config found at argConfig path, repeatedly asks user for path & validates it
     * @param argConfig config path supplied by program arguments
     * @return string valid config path
     */
    static string m_GetMainConfigPath(char * argConfig);

    /**
     * Loads contents of file at provided configPath.
     *
     * Returns contents as string
     * @warning throws if file empty
     * @param configPath file path to load from
     * @return file contents string
     */
    static string m_GetConfigString(const string &configPath);

    /**
     * Processes m_configString variable.
     *
     * Removes comments, processes scene/object config definitions and creates their
     * respective prefix for further parameters processing.
     */
    void m_ProcessConfigString();

    /**
     * Processes m_configString variable
     *
     * Loads parameters under provided prefix until next Scene/Object found.
     * @param prefix prefix to save parameters under
     */
    void m_ProcessParameters(const string &prefix);

    /**
     * Processes config defined items.
     *
     * Loads items defined in config to the items vector.
     * @warning items must start form index 0 and increment.
     */
    void m_ProcessItems();

    /**
     * Processes config defined levels.
     *
     * Loads levels defined in config to the levels vector.
     * @warning levels must start form index 0 and increment.
     */
    void m_ProcessLevels();

private:
    string m_configString; /// Contents of current config file for processing
    map<string, string> m_configData; /// Map with parameters loaded from config file
    vector<int> m_sceneObjectCounts; /// Vector with counts of objects in each scene

    string m_playerDataPath; /// Current player data file path

    // Preprocessed data
    vector<Level> m_levels; /// Config defined levels vector
    vector<Item> m_items; /// Config defined items vector
};
