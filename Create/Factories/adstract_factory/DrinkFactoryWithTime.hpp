#pragma once
#include "CoffeeFactory.hpp"
#include <functional>
#include <string>
#include <memory>
#include <map>

class DrinkFactoryWithTime
{
private:
  map<string, function<unique_ptr<Coffee>()>> coffeefactories;
public:
  DrinkFactoryWithTime();
  unique_ptr<Coffee> make_drink(const string);
};