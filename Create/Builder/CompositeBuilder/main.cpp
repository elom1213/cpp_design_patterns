//original code
//https://github.com/mpavezb/cpp_design_patterns/tree/master/Creational/builder/facade

#include "Menu.hpp"
#include "MenuBuilder.hpp"
#include "MainMenuBuilder.hpp"
#include "DrinkBuilder.hpp"
#include <iostream>

using namespace std;

/*
Menu is a complex class
we do not want to have big constructors.

We want 2 builders: DrinkBuilder and MainMenuBuilder.
The implementation logic requires the creation of 4 builder classes:
- MenuBuilderBase: Base class helps us to chain different types of builders.
- MenuBuilder: Only purpose is to keep the actual object.

Other builders work using a reference to it. This way, we avoid
multiple copies and destructions of the object in the chain.
- DrinkBuilder: Creates drink related fields.
- MainMenuBuilder: Creates main menu related fields.
*/


int main() {
  Menu lunch = Menu::create()
                     .drink().type("Coffee")
                             .size("Big")
                 .main_menu().type("Sandwich")
                             .fillings("Chicken");

  cout << lunch << endl;
}