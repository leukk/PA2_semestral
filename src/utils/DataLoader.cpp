#include "DataLoader.h"

DataLoader::DataLoader() : m_configString(), m_configData(map<string,string>()), m_sceneObjectCounts(vector<int>()){
}

string DataLoader::m_GetMainConfigPath(WINDOW * interactionWin, char * argConfig){
    string configPath;
    if(!argConfig)
        wprintw(interactionWin, "No config passed as argument.\n");
    else
        configPath = argConfig;
    wrefresh(interactionWin);

    // Try open ifstream of main config file
    ifstream configStream(configPath);
    while(!configStream.is_open()){
        char inputPath[200];

        wprintw(interactionWin, "Could not open config file, try entering path again or abort by typing X:\n");
        wrefresh(interactionWin);

        echo();
        getnstr(inputPath, 199);
        noecho();

        configPath = inputPath;
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
        throw invalid_argument("No config path provided\n");

    // Open config file
    ifstream configStream(configPath);

    // Throw if file cannot be open
    if(!configStream.is_open())
        throw invalid_argument("Invalid config path provided\n");

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

    int sharedParams = SHARED_PARAMETERS;
    int sceneIndex = SHARED_PARAMETERS;
    while (true){
        int objectIndex = SHARED_PARAMETERS;
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

bool DataLoader::LoadMainConfig(WINDOW *interactionWin, char * argConfig) {
    try{
        // Try to validate or get config path from user
        string cfgPath = m_GetMainConfigPath(interactionWin, argConfig);
        if(cfgPath.empty())
            return false;

        // Load config from file into string & process it
        m_configString = m_GetConfigString(cfgPath);
        m_ProcessConfigString();
    }
    catch (invalid_argument& e){
        wprintw(interactionWin, "Config processing failed at:\n%50s\nReason: %s", m_configString.c_str(), e.what());
        wrefresh(interactionWin);
        getch();
        return false;
    }
    catch (exception& e) {
        wprintw(interactionWin, "Failed to load config, reason: %s\n", e.what());
        wrefresh(interactionWin);
        getch();
        return false;
    }

    wprintw(interactionWin, "Config loaded, found:\n"
                            "%lu scenes containing %lu parameters\n",
                            m_sceneObjectCounts.size(), m_configData.size());
    wrefresh(interactionWin);
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
        throw invalid_argument("Couldn't find value pair of: " + key.str());
    return valueIt->second;
}

int DataLoader::ConfigGetNumParam(int sceneIndex, int objectIndex, const string &param) const{
    string stringValue = ConfigGetParam(sceneIndex, objectIndex, param);
    int numValue = 0;
    try {
        numValue = stoi(stringValue);
    }
    catch (exception& e){
        throw invalid_argument("Failed conversion of \"" + stringValue + "\" to number");
    }
    return numValue;
}
