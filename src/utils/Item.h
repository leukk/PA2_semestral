#pragma once
#include <string>

using std::string;

struct Item{
    Item() = default;
    Item(const Item& other) = default;
    ~Item() = default;
    string title{};
    int price = 0;
    string effect{};
    int effectChange = 0;
};