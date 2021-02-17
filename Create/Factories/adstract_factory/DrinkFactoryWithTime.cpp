#include <functional>
#include <memory>
#include <map>
#include <string>
#include "DrinkFactoryWithTime.hpp"

using namespace std;

template<typename T, int time>
unique_ptr<Coffee> set_coffee_preparing_time();

DrinkFactoryWithTime::DrinkFactoryWithTime()
{
  coffeefactories["Latte"] = set_coffee_preparing_time<Latte, 4>;
  coffeefactories["Americano"] = set_coffee_preparing_time<Americano, 3>;
  coffeefactories["Caffemocha"]  = set_coffee_preparing_time<Caffemocha, 6>;
}

unique_ptr<Coffee> 
DrinkFactoryWithTime::make_drink(const string type)
{
  return coffeefactories[type]();
}

template<typename T, int time>
unique_ptr<Coffee> set_coffee_preparing_time()
{
  auto coffee = make_unique<T>();
  coffee->prepare(time);
  return coffee;
}