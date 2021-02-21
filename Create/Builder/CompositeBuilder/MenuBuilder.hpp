#pragma once
#include "Menu.hpp"

class DrinkBuilder;
class MainMenuBuilder;

// use this class as a base, keeping a reference to Menu object.
// That is because we do not want the Menu to be replicated each time.
// The actual Menu is kept in the MenuBuilder, and each builder
// derives from MenuBuilderBase.

class MenuBuilderBase
{
protected:
  Menu& menu;
  MenuBuilderBase(Menu& m) : menu{m} {}
public:
  operator Menu() const { return std::move(menu); }
  virtual DrinkBuilder drink() const;
  virtual MainMenuBuilder main_menu() const;
};

class MenuBuilder : public MenuBuilderBase
{
  Menu m;
public:
  MenuBuilder() : MenuBuilderBase{m} {}
};