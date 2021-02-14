#pragma once
#include <iostream>
#include <string>
#include "Fillings.hpp"

using namespace std;

struct SubwayMenu
{
  string name;
  Fillings* fillings;

  SubwayMenu(SubwayMenu& other) :
  fillings{new Fillings{*other.fillings}},
  name{other.name} {}

  SubwayMenu(const string name, Fillings& fillings_) :
  fillings{new Fillings{fillings_}},
  name{name} {}

  SubwayMenu(const string name, Fillings* fillings_) : 
  fillings{fillings_}, name{name} 
  {fillings_ = nullptr;}

  friend ostream& operator<<(ostream& os, SubwayMenu& menu)
  {
    os << "you ordered "<< menu.name  << endl; 
    os << "It filled with " << menu.fillings->filling1 << ", " << menu.fillings->filling2 << endl;
    os << "And you choose " << menu.fillings->sauce << endl;
    return os;
  }
};
