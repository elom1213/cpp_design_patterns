#pragma once

#include <iostream>
#include <string>

using namespace std;

class MenuBuilder;

class Menu
{
  string drink;
  string drink_size;
  string main_menu;
  string filling;
  Menu(){};

public:
  ~Menu(){};
  Menu(Menu&& menu):
  drink{menu.drink},
  drink_size{menu.drink_size},
  main_menu{menu.main_menu},
  filling{menu.filling} {}

  static MenuBuilder create();

  friend class MenuBuilderBase;
  friend class MenuBuilder;
  friend class DrinkBuilder;
  friend class MainMenuBuilder;

  friend std::ostream& operator<<(std::ostream& os, const Menu& m)
  {
    os << "you ordered " << m.drink_size << " size " << m.drink << '\n';
    os << "your main dish is " << m.main_menu << " filed with " << m.filling;
    return os;
  }
};