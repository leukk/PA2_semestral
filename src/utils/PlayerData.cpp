#include "PlayerData.h"

void PlayerData::Write(ofstream &output) {
    m_WriteNumVector(output, equippedItems);
    m_WriteNumVector(output, ownedItems);
    m_WriteNum(output, nextLevelIndex);
    m_WriteNum(output, role);
    m_WriteNum(output, coins);
    m_WriteNum(output, moveDelay);
    m_WriteNum(output, lives);
    m_WriteNum(output, attackRange);
}

void PlayerData::Read(ifstream &input) {
    m_ReadNumVector(input, equippedItems);
    m_ReadNumVector(input, ownedItems);
    m_ReadNum(input, nextLevelIndex);
    m_ReadNum(input, role);
    m_ReadNum(input, coins);
    m_ReadNum(input, moveDelay);
    m_ReadNum(input, lives);
    m_ReadNum(input, attackRange);
}

void PlayerData::m_WriteNumVector(ofstream& output, vector<int>& vec) {
    output << CONF_VALUE_DELIM;
    for(auto it : vec){
        output << it << " ";
    }
    output << CONF_VALUE_DELIM;
    output << "\n";
}

void PlayerData::m_WriteNum(ofstream& output, int num) {
    output << CONF_VALUE_DELIM << num << CONF_VALUE_DELIM << "\n";
}

void PlayerData::m_ReadNumVector(ifstream &input, vector<int> &vec) {
    vec.clear();
    if(!input.is_open())
        return;

    string lineValue = m_GetLineValue(input);
    if(lineValue.empty())
        return;

    int readVal;
    istringstream lineLoader(lineValue);
    while (lineLoader.good()){
        lineLoader >> readVal;
        if(lineLoader.good())
            vec.push_back(readVal);
    }
}

void PlayerData::m_ReadNum(ifstream &input, int &num) {
    string lineValue = m_GetLineValue(input);
    istringstream lineLoader(lineValue);
    lineLoader >> num;
}

string PlayerData::m_GetLineValue(ifstream &input){
    string line;
    getline(input, line);
    size_t valStart = line.find(CONF_VALUE_DELIM);
    size_t valEnd = line.find(CONF_VALUE_DELIM, valStart+1);
    return line.substr(valStart+1, valEnd-valStart-1);
}
