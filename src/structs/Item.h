#pragma once
#include <string>

using std::string;

struct Item{
    Item() = default;
    Item(const Item& other) = default;
    ~Item() = default;
    string title{}; /// Title of item
    int price = 0; /// Price of item
    int effect = -1; /// Effect index change
    int effectChange = 0; /// Effect change amount
};