#pragma once

#include "MenuBuilder.hpp"
#include <string>

using namespace std;

class DrinkBuilder : public MenuBuilderBase
{
  using self = DrinkBuilder;
public:
  DrinkBuilder(Menu& m) : MenuBuilderBase{m} {}
  self& type(const string& drink)
  {
    menu.drink = drink;
    return *this;
  }
  self& size(const string& size)
  {
    menu.drink_size = size;
    return *this;
  }
};