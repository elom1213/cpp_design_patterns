#pragma once

#include "MenuBuilder.hpp"
#include <string>

using namespace std;

class MainMenuBuilder : public MenuBuilderBase
{
  using self = MainMenuBuilder;
public:
  MainMenuBuilder(Menu& m) : MenuBuilderBase{m} {}
  self& type(const string& main_menu)
  {
    menu.main_menu = main_menu;
    return *this;
  }
  self& fillings(const string& filling)
  {
    menu.filling = filling;
    return *this;
  }
};