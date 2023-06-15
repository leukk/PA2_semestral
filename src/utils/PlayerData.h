#pragma once
#include "GameConstants.h"
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using std::string, std::vector;
using std::ifstream, std::ofstream;
using std::istringstream, std::ostringstream;

/**
 * Struct containing savable player data
 */
struct PlayerData{
    PlayerData() = default;
    PlayerData(const PlayerData& other) = default;
    ~PlayerData() = default;

    /**
     * Writes data to output file stream
     *
     * Writes data in a particular order to filestream.
     * This order is later used when reading the data.
     * @param output out file stream
     */
    void Write(ofstream &output);
    /**
     * Reads data from input file stream
     *
     * Reads data in a particular order from filestream.
     * Reading order matches writing order.
     * @param input in file stream
     */
    void Read(ifstream &input);

    vector<int> equippedItems{}; /// Indexes of currently equipped items - indexes match items defined in main config
    vector<int> ownedItems{}; /// Indexes of currently owned items - indexes match items defined in main config
    int nextLevelIndex = 0; /// Index of next level definition to load from config
    int role = 0; /// Role index - game supports 3 roles (0,1,2)
    int coins = 3; /// Player owned currency
    int moveDelay = 8; /// Mode delay bonus - subtracted from config defined move delay
    int lives = 2; /// Lives bonus - added to config defined lives
    int attackRange = 2; /// Attack range bonus - added to config defined attack range

private:
    /**
    * Writes numbers vector to output file stream
    *
    * Numbers are written inline, separated by spaces
    * The entire value string is enclosed in quotation marks
    * @param output out file stream
    * @param vec numbers vector to write
    */
    static void m_WriteNumVector(ofstream& output, vector<int>& vec);
    /**
     * Writes a single number to output file stream
     *
     * Value gets enclose in quotation marks
     * @param output out file stream
     * @param num number to write
     */
    static void m_WriteNum(ofstream& output, int num);
    /**
    * Reads numbers vector from input file stream
    *
    * Numbers in the input file stream are expected to be written inline,
    * separated by spaces. The read value should be enclosed in quotation marks
    * @param input in file stream
    * @param vec reading output numbers vector
    */
    static void m_ReadNumVector(ifstream& input, vector<int>& vec);
    /**
    * Reads single value from file input stream.
    *
    * Reads single value enclosed in quotation marks.
    * @param input in file stream
    * @return reading output number
    */
    static void m_ReadNum(ifstream& input, int& num);
    /**
     * Reads value enclosed in quotation marks from a single line as string.
     *
     * @param input in file stream
     * @return string value with removed quotation marks
     */
    static string m_GetLineValue(ifstream &input);
};


