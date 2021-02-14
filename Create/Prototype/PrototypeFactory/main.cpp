#include "MenuFactory.hpp"
#include <iostream>

using namespace std;

int main() {
  Fillings myfill{"chicken", "tomato", "sweet sauce"};
  // using SubwayMenu ctor directly
  // SubwayMenu(const string , Fillings& )
  SubwayMenu mymenu{"sweet chicken", myfill};
  // SubwayMenu(SubwayMenu&)
  SubwayMenu friendmenu{mymenu};

  // using MenuFactory
  // choose menu's name and youre favorit sauce
  // it gives prototype of each menu
  auto classicHam = MenuFactory::NewClassic("classicHam", "honey mustard");
  auto steakAndCheese = MenuFactory::NewPremium("steakAndCheese", "sweet chilli sauce");
  
  cout << mymenu << endl;
  cout << friendmenu << endl;
  cout << *classicHam << endl;
  cout << *steakAndCheese;
}