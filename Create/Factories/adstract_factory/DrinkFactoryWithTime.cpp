#include <functional>
#include <memory>
#include <map>
#include <string>
#include "DrinkFactoryWithTime.hpp"

using namespace std;

template<typename T, int time>
unique_ptr<Coffee> coffeeFun();

DrinkFactoryWithTime::DrinkFactoryWithTime()
{
  coffeefactories["Latte"] = coffeeFun<Latte, 4>;
  coffeefactories["Americano"] = coffeeFun<Americano, 3>;
  coffeefactories["Caffemocha"]  = coffeeFun<Caffemocha, 6>;
}

unique_ptr<Coffee> 
DrinkFactoryWithTime::make_drink(const string type)
{
  return coffeefactories[type]();
}

template<typename T, int time>
unique_ptr<Coffee> coffeeFun()
{
  auto coffee = make_unique<T>();
  coffee->prepare(time);
  return coffee;
}