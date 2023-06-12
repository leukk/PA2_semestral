#include "DataLoader.h"

DataLoader::DataLoader() : m_configString(), m_configData(map<string,string>()), m_sceneObjectCounts(vector<int>()){
}

string DataLoader::GetInputString(const string& prompt){
    char inputBuffer[200];

    wclear(GameManager::GetTextWindow());
    mvwprintw(GameManager::GetTextWindow(),1,0, "%s:\n ", prompt.c_str());
    GameManager::RefreshWindows();

    nodelay(GameManager::GetTextWindow(), false);
    echo();
    wgetnstr(GameManager::GetTextWindow(), inputBuffer, 199);
    noecho();
    nodelay(GameManager::GetTextWindow(), true);

    GameManager::RefreshWindows();
    return {inputBuffer};
}

bool DataLoader::LoadMainConfig(char * argConfig) {
    ostringstream errorMsg;
    try{
        // Try to validate or get config path from user
        string cfgPath = m_GetMainConfigPath(argConfig);
        if(cfgPath.empty())
            return false;

        // Load config from file into string & process it
        m_configString = m_GetConfigString(cfgPath);
        m_ProcessConfigString();
    }
    catch (invalid_argument& e){
        errorMsg << " Config processing failed at:\n" << m_configString.substr(0,50) << "\n";
        errorMsg << " Reason: " << string(e.what()) << "\n";
        GameManager::ShowError(errorMsg.str());
        return false;
    }
    catch (exception& e) {
        errorMsg << " Failed to load config, reason: " << string(e.what()) << "\n";
        GameManager::ShowError(errorMsg.str());
        return false;
    }

    m_ProcessItems();
    m_ProcessLevels();

    wprintw(GameManager::GetTextWindow(), " Config loaded, found:\n"
                            " %lu scenes containing %lu parameters\n",
            m_sceneObjectCounts.size(), m_configData.size());
    wrefresh(GameManager::GetTextWindow());
    return true;
}

size_t DataLoader::ConfigSceneCount() const {
    return m_sceneObjectCounts.size();
}

size_t DataLoader::ConfigObjectCount(int sceneIndex) const{
    return m_sceneObjectCounts[sceneIndex];
}

string DataLoader::ConfigGetParam(int sceneIndex, int objectIndex, const string &param) const{
    ostringstream key;
    key << sceneIndex << CONF_PREFIX_DELIM << objectIndex << CONF_PREFIX_DELIM << param;
    auto valueIt = m_configData.find(key.str());
    if(valueIt == m_configData.end())
        return {};
    return valueIt->second;
}

int DataLoader::ConfigGetNumParam(int sceneIndex, int objectIndex, const string &param) const{
    // Get param string value
    string stringValue = ConfigGetParam(sceneIndex, objectIndex, param);

    // Implicitly convert missing/empty parameter to 0
    if(stringValue.empty())
        return 0;

    // If string has contents, convert to number via stoi
    int numValue = 0;
    try {
        numValue = stoi(stringValue);
    }
    catch (exception& e){
        throw invalid_argument("Failed conversion of \"" + stringValue + "\" to number");
    }
    return numValue;
}

const vector<Level> &DataLoader::ConfigLevels() {
    return m_levels;
}

const vector<Item> &DataLoader::ConfigItems() {
    return m_items;
}

void DataLoader::SetPlayerDataFilePath() {
    m_playerDataPath.clear();
    while (m_playerDataPath.empty())
        m_playerDataPath = GetInputString(" Enter non-empty player save name:");
}

void DataLoader::UnsetPlayerDataFilePath() {
    m_playerDataPath.clear();
}

void DataLoader::LoadPlayerData() {
    ifstream playerDataFile(m_playerDataPath, std::ios::in);
    if(!playerDataFile.is_open())
        throw invalid_argument(" Failed to open playerData, cannot open or create file");

    playerData.Read(playerDataFile);
    playerDataFile.close();
}

void DataLoader::SavePlayerData() {
    ofstream playerDataFile(m_playerDataPath, std::ios::out | std::ios::trunc);
    if(!playerDataFile.is_open())
        throw invalid_argument(" Failed to save playerData, cannot open or create file");

    playerData.Write(playerDataFile);
    playerDataFile.close();
}

void DataLoader::SetDefaultPlayerStats() {
    playerData = PlayerData();
}

const string& DataLoader::PlayerDataPath() {
    return m_playerDataPath;
}

string DataLoader::m_GetMainConfigPath(char * argConfig){
    string configPath;
    if(!argConfig)
        GameManager::ShowError(" No config passed as argument.\n");
    else
        configPath = argConfig;

    // Try open ifstream of main config file
    ifstream configStream(configPath);
    while(!configStream.is_open()){
        configPath = GetInputString(" Could not open config file, try entering path again or abort by typing 'X'");
        if(configPath == "x" || configPath == "X")
            return {};

        configStream.open(configPath);
    }

    // Found file which can be read
    configStream.close();
    return configPath;
}

string DataLoader::m_GetConfigString(const string &configPath) {
    if(configPath.empty())
        throw invalid_argument(" No config path provided\n");

    // Open config file
    ifstream configStream(configPath);

    // Throw if file cannot be open
    if(!configStream.is_open())
        throw invalid_argument(" Invalid config path provided\n");

    // Read file into ostringstream and return its string
    string line;
    ostringstream output;
    while (configStream.good()){
        getline(configStream, line);

        // Remove line comments (text following comment delimiter)
        size_t commentPos = line.find(CONF_COMMENT_DELIM);
        if(commentPos != string::npos)
            line = line.substr(0,commentPos);

        output << line;
    }

    string configString = output.str();

    if(configString.empty())
        throw invalid_argument("Config file empty\n");

    return configString;
}

void DataLoader::m_ProcessConfigString() {
    size_t nextScene, nextObject;
    ostringstream prefix;

    int sharedParams = SHARED_DATA;
    int sceneIndex = SHARED_DATA;
    while (true){
        int objectIndex = SHARED_DATA;
        while (true){
            prefix.str("");
            prefix << sceneIndex << CONF_PREFIX_DELIM << objectIndex << CONF_PREFIX_DELIM;

            // Read parameters until next scene or object
            m_ProcessParameters(prefix.str());

            nextScene = m_configString.find(CONF_SCENE_DELIM);
            nextObject = m_configString.find(CONF_OBJECT_DELIM);

            // End if no more objects from current scene to be processed or no objects left at all
            if(nextObject == string::npos || nextObject > nextScene){
                // Add scene & number of objects if not dealing with shared params
                if(sceneIndex!=sharedParams && objectIndex!=sharedParams)
                    m_sceneObjectCounts.push_back(objectIndex+1);
                break;
            }

            // Else continue & remove blocking object prefix
            m_configString = m_configString.substr(nextObject + string(CONF_OBJECT_DELIM).size());
            objectIndex++;
        }

        // End if no more scenes remaining
        if(nextScene == string::npos)
            break;

        // Else continue & remove blocking scene prefix
        m_configString = m_configString.substr(nextScene + string(CONF_SCENE_DELIM).size());
        sceneIndex++;
    }
}

void DataLoader::m_ProcessParameters(const string& prefix){
    // Parameter & value start & end positions
    size_t paramStart, paramEnd, valueStart, valueEnd;
    size_t nextScene, nextObject, stopPos;
    ostringstream key;
    string value;
    while (true){
        key.str("");
        value.clear();

        nextScene = m_configString.find(CONF_SCENE_DELIM);
        nextObject = m_configString.find(CONF_OBJECT_DELIM);
        stopPos = min(nextObject, nextScene);

        // Process parameter only if one exists / exists before another scene or object
        paramStart = m_configString.find(CONF_PARAM_START_DELIM);
        if(paramStart == string::npos || paramStart > stopPos)
            return;

        // Get parameter key and value start/end
        paramEnd = m_configString.find(CONF_PARAM_END_DELIM, paramStart);
        valueStart = m_configString.find(CONF_VALUE_DELIM, paramStart);
        valueEnd = m_configString.find(CONF_VALUE_DELIM, valueStart+1);

        if(valueStart == string::npos || valueEnd == string::npos)
            throw invalid_argument("Missing value delimiters of parameter\n");

        if(paramEnd == string::npos || paramEnd > valueStart)
            throw invalid_argument("Missing space between parameter key and value\n");

        // Create key & value to insert to map
        key << prefix << m_configString.substr(paramStart, paramEnd - paramStart);
        value = m_configString.substr(valueStart+1, valueEnd-valueStart-1);

        // Insert key-value pair into map
        m_configData.insert(std::make_pair(key.str(), value.c_str()));

        // Leave only part after parameter value
        m_configString = m_configString.substr(valueEnd+1);
    }
}

void DataLoader::m_ProcessLevels() {
    size_t levelIndex = 0;
    Level newLevel;
    while(true){
        newLevel.title = ConfigGetParam(SHARED_DATA, SHARED_DATA, PARAM_LEVEL_TITLE_PREFIX + to_string(levelIndex));
        if(newLevel.title.empty())
            break;
        newLevel.description = ConfigGetParam(SHARED_DATA, SHARED_DATA, PARAM_LEVEL_DESCRIPTION_PREFIX + to_string(levelIndex));
        if(newLevel.description.empty())
            break;
        newLevel.sceneIndex = ConfigGetNumParam(SHARED_DATA, SHARED_DATA, PARAM_LEVEL_SCENE_INDEX_PREFIX + to_string(levelIndex));
        newLevel.reward = ConfigGetNumParam(SHARED_DATA, SHARED_DATA, PARAM_LEVEL_REWARD_PREFIX + to_string(levelIndex));

        levelIndex++;
        m_levels.push_back(newLevel);
    }
}

void DataLoader::m_ProcessItems() {
    size_t itemIndex = 0;
    Item newItem;
    while(true){
        newItem.title = ConfigGetParam(SHARED_DATA, SHARED_DATA, PARAM_ITEM_TITLE_PREFIX + to_string(itemIndex));
        if(newItem.title.empty())
            break;
        newItem.price = ConfigGetNumParam(SHARED_DATA, SHARED_DATA, PARAM_ITEM_PRICE_PREFIX + to_string(itemIndex));
        if(newItem.price == 0)
            break;
        newItem.effect = ConfigGetNumParam(SHARED_DATA, SHARED_DATA, PARAM_ITEM_EFFECT_PREFIX + to_string(itemIndex));
        newItem.effectChange = ConfigGetNumParam(SHARED_DATA, SHARED_DATA, PARAM_ITEM_EFFECT_CHANGE_PREFIX + to_string(itemIndex));
        itemIndex++;
        m_items.push_back(newItem);
    }
}










