#pragma once
#include <string>

using std::string;

struct Item{
    Item() = default;
    Item(const Item& other) = default;
    ~Item() = default;
    string title{};
    int price = 0;
    int effect = -1;
    int effectChange = 0;
};