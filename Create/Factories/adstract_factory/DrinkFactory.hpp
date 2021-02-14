#pragma once
#include "CoffeeFactory.hpp"
#include <string>
#include <memory>
#include <map>

using namespace std;

class DrinkFactory
{
private:
  map<string, unique_ptr<CoffeeFactory>> coffeefactories;
public:
  DrinkFactory();
  unique_ptr<Coffee> make_drink(const string&);
};
